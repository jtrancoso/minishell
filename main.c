/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/29 13:48:16 by jtrancos         ###   ########.fr       */
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
		read(0, line, BUFFERSIZE - 1);
		ft_parseline(&comm, &split, line);
		//test_list(list, &comm); //para comprobar los dolares
		/*if (ft_strncmp(line, "exit", 4) == 0)
		{
			ft_lstclear(&comm.env_head, &free_env);
			ft_lstclear(&comm.parse_head, &free_list);
			free(comm.user);
			break;
		}*/
		list = comm.parse_head;
		while (list)
		{
			if (((t_comm*)list->content)->t_word)
				parse_command(list, &comm, &split); //TODO:HABRIA QUE LLAMARLO MIENTRAS HAYA WORDS EN LIST
			list = list->next;
		}
		ft_lstclear(&comm.parse_head, &free_list);
	}
	return (0);
}
