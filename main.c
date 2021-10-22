/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/22 13:11:35 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void miraleaks()
{
	system("leaks minishell");
}

char *next_shlvl(char *shlvl)
{
	char *aux;
	int lvl;

	lvl = ft_atoi(shlvl) + 1;
	aux = shlvl;
	shlvl = ft_itoa(lvl);
	free (aux);
	return(shlvl);
}

int main (int argv, char **argc, char **envp)
{
	t_list *list;
	t_list *new;
	t_env *env;
	t_comm comm;
	t_split split;

	//atexit(miraleaks);
	char line[BUFFERSIZE];
	write(1, "\033[1;33m", 7);
	printf("             _            _   _             _          _ _  \n  __ _  __ _| | __ _  ___| |_(_) ___    ___| |__   ___| | | \n / _` |/ _` | |/ _` |/ __| __| |/ __|  / __| '_ \\ / _ \\ | | \n| (_| | (_| | | (_| | (__| |_| | (__   \\__ \\ | | |  __/ | | \n \\__, |\\__,_|_|\\__,_|\\___|\\__|_|\\___|  |___/_| |_|\\___|_|_| \n |___/                                                      \n\n");
	write(1, "\033[0m", 4);
	char **split_env;
	comm.env_head = NULL;
	int i = 0;
	if (!envp[i])
	{
		char *aux;
		i = 0;
		split_env = malloc(sizeof(char *) * 7);
		while (i < 6)
		{
			split_env[i] = malloc(sizeof(char ) * 50);
			i++;
		}
		aux = ft_strjoin("PWD=", getcwd(NULL, 0));
		split_env[i] = NULL;
		split_env[0] = "SHLVL=0";
		split_env[1] = aux;
		split_env[2] = "_=./minishell"; //FIXME: actualizar con el historial
		split_env[3] = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin";
		split_env[4] = "USER=unknown";
		split_env[5] = "OLDPWD= ";
		i = 0;
		char **new_split;
		while (split_env[i])
		{
			new = malloc(sizeof(t_list));
			env = malloc(sizeof(t_env));
			new_split = ft_split(split_env[i], '=');
			new->content = env;
			((t_env*)new->content)->id = new_split[0];
			((t_env*)new->content)->value = new_split[1];
			ft_lstadd_back(&comm.env_head, new);
			free(new_split);
			i++;
		}
		free(aux);
	}
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		split_env = ft_split(envp[i], '=');
		new->content = env;
		((t_env*)new->content)->id = split_env[0];
		((t_env*)new->content)->value = split_env[1];
		ft_lstadd_back(&comm.env_head, new);
		free(split_env);
		i++;
	}
	list = comm.env_head;
	while (list)
	{
		if (ft_strncmp(((t_env*)list->content)->id, "USER", 4) == 0)
			comm.user = ft_strdup(((t_env*)list->content)->value);
		else if (ft_strncmp(((t_env*)list->content)->id, "SHLVL", 5) == 0)
			((t_env*)list->content)->value = next_shlvl(((t_env*)list->content)->value);
		list = list->next;
	}
	split.errorcode = 0; //esto sirve para el $? en principio
	while (1)
	{
		comm.parse_head = NULL;
		ft_bzero(line, BUFFERSIZE - 1);
		write(1, "\033[1;36m", 7);
		write(1, comm.user , ft_strlen(comm.user));
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
		read(0, line, BUFFERSIZE - 1); //TODO: crear un int que a = read, si es 0 exit para ctrl+D
		ft_parseline(&comm, &split, line);
		//test_list(list, &comm); //para comprobar los dolares
		list = comm.parse_head;
		i = 1;
		while (list)
		{
			if (((t_comm*)list->content)->t_pipe == 0)
				((t_comm*)list->content)->page = i;
			if (((t_comm*)list->content)->t_pipe == 1)
			{
				((t_comm*)list->content)->page = 0;
				i++;
			}
			list = list->next;
		}
		test_list(list, &comm);
		list = comm.parse_head;
		while (list)
		{
			if (((t_comm*)list->content)->t_word == NULL)
				parse_redir(list, &comm, &split);
			printf("gt: %d file fuera: %s\n", ((t_comm*)list->content)->t_gt, ((t_comm*)list->content)->redir.file);
			list = list->next;
		}
		//test_list(list, &comm);
		list = comm.parse_head;
		i = 1;
		char *str;
		char *aux;
		int fdin;
		int fdout;

		fdin = 0;
		fdout = 0;
		while (list)
		{
			str = NULL;
			while ((((t_comm*)list->content)->page) == i)
			{
				if (((t_comm*)list->content)->t_word && !str)
				{
					str = ft_strdup(((t_comm*)list->content)->t_word);
					((t_comm*)list->content)->f_exec = 1;
				}
				else if (!((t_comm*)list->content)->t_word && str)
				{
					aux = str;
					if (((t_comm*)list->content)->redir.rest)
					{
						str = ft_strjoin(str, ((t_comm*)list->content)->redir.rest);
						free (aux);
					}
					if (fdin)
						close(fdin);
					if (((t_comm*)list->content)->t_gt)
						fdin = open(((t_comm*)list->content)->redir.file, O_RDWR | O_TRUNC | O_CREAT, 0700);
					if (((t_comm*)list->content)->t_gtgt)
						fdin = open(((t_comm*)list->content)->redir.file, O_RDWR | O_APPEND | O_CREAT, 0700);
				}
				if ((list->next && (((t_comm*)list->next->content)->page) == 0) || !list->next)
				{
					((t_comm*)list->content)->t_command = ft_strdup(str);
					if (str)
						free(str);
					((t_comm*)list->content)->redir.last_fdin = fdin;
					parse_command(list, &comm, &split);
					if (fdin)
					{
						((t_comm*)list->content)->redir.last_fdin = 1;
						close(fdin);
					}
					i++;
					if (list->next)
						list = list->next;
				}
				if (list->next || ((t_comm*)list->content)->page == 0)
				{
					if (((t_comm*)list->content)->page == 0)
						str = NULL;
					list = list->next;
				}
			}
			list = list->next;
		}
		ft_lstclear(&comm.parse_head, &free_list);
	}
	return (0);
}
