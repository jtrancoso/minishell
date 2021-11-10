/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/10 10:30:09 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void miraleaks()
{
	system("leaks minishell");
}

int main (int argv, char **argc, char **envp)
{
	t_list *list;
	t_list *new;
	t_env *env;
	t_comm comm;
	t_split split;
	int i;

	atexit(miraleaks);
	char line[BUFFERSIZE];
	print_prompt(&comm);
	comm.env_head = NULL;
	char **split_env;
	i = 0;
	if (!envp[i])
		galactic_env(&comm);
	i = 0;
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
	split.errorcode = 0;
	while (1)
	{
		int ctrld;
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, default_sigquit);
		comm.parse_head = NULL;
		ft_bzero(line, BUFFERSIZE);
		ctrld = read(0, line, BUFFERSIZE); //TODO: crear un int que a = read, si es 0 exit para ctrl+D
		if (ctrld == 0)
			ctrl_d(&split, line, ctrld);
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		//printf("%s\n", line);
		ft_parseline(&comm, &split, line); //Parseo de línea para su preparación y búsqueda de errores quotes abiertas y backslashes abiertos
		//test_list(list, &comm); //para comprobar los dolares
		list = comm.parse_head;
		i = 1;
		while (list)
		{
			if (((t_comm*)list->content)->t_pipe == 0 || ((t_comm*)list->content)->t_semi == 0)
				((t_comm*)list->content)->page = i;
			if (((t_comm*)list->content)->t_pipe == 1 || ((t_comm*)list->content)->t_semi == 1)
			{
				((t_comm*)list->content)->page = 0;
				i++;
			}
			list = list->next;
		}
		//test_list(list, &comm);
		list = comm.parse_head;
		while (list)
		{
			if (((t_comm*)list->content)->t_word == NULL)
				parse_redir(list, &comm, &split);
			list = list->next;
		}
		list = comm.parse_head;
		while (list)
		{
			if (((t_comm*)list->content)->t_word != NULL && list->next)
			{
				if (((t_comm*)list->next->content)->t_pipe == 1)
					((t_comm*)list->content)->post_pipe = 1;
			}
			if (((t_comm*)list->content)->t_pipe == 1)
			{
				if (((t_comm*)list->next->content)->t_word != NULL)
					((t_comm*)list->next->content)->prev_pipe = 1;
			}
			list = list->next;
		}
		test_list(list, &comm);
		list = comm.parse_head;
		i = 1;
		char *str;
		char *aux;
		int fdin;
		int fdout;     //TODO: todo estos fd a la estructura
		int real_fdout;
		int	real_fdin;
		int *fd; //TODO: habra que meterlo en la funcion correspondiente

		fdin = 0;
		fdout = 0;
		fd = malloc(sizeof(int) * 2);
		while (list)
		{
			str = NULL;
			while ((((t_comm*)list->content)->page) == i)
			{
				if (((t_comm*)list->content)->t_word && !str)
					str = ft_strdup(((t_comm*)list->content)->t_word);
				else if (!((t_comm*)list->content)->t_word && str)
				{
					aux = str;
					if (((t_comm*)list->content)->redir.rest)
					{
						str = ft_strjoin(str, ((t_comm*)list->content)->redir.rest);
						free (aux);
					}
					if (fdout)
						close(fdout);
					if (fdin)
						close(fdin);
					if (((t_comm*)list->content)->t_gt)
						fdout = open(((t_comm*)list->content)->redir.file, O_RDWR | O_TRUNC | O_CREAT, 0700);
					if (((t_comm*)list->content)->t_gtgt)
						fdout = open(((t_comm*)list->content)->redir.file, O_RDWR | O_APPEND | O_CREAT, 0700);
					if (fdout)
						real_fdout = dup(1);
					if (((t_comm*)list->content)->t_lt)
						fdin = open(((t_comm*)list->content)->redir.file, O_RDONLY);
					if (fdin)
						real_fdin = dup(0);
				}
				if ((list->next && ((((t_comm*)list->next->content)->page) == 0)) || !list->next)
				{
					((t_comm*)list->content)->t_command = ft_strdup(str);
					if (str)
						free(str);
					if (fdout)
						dup2(fdout, 1);
					if (fdin)
						dup2(fdin, 0);
					parse_command(list, &comm, &split);
					//test_list(list, &comm);
					if (fdout)
					{
						close(fdout);
						dup2(real_fdout, 1);
						close (real_fdout);
					}
					if (fdin)
					{
						close(fdin);
						dup2(real_fdin, 0);
						close(real_fdin);
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
		print_user(&comm);
		ft_lstclear(&comm.parse_head, &free_list);
	}
	return (0);
}
