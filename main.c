/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/11 18:56:40 by jtrancos         ###   ########.fr       */
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

	//atexit(miraleaks);
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
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, default_sigquit);
		our_read_line(&comm, &split);
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		ft_parseline(&comm, &split, NULL);
		free(comm.final_line);
		comm.final_line = NULL;
		list = comm.parse_head;
		//printf("1: %s\n", ((t_comm*)list->content)->t_word);
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
		/*int page;					//TODO: por lo que he estado viendo con mario esto no hace tanta falta porque los > | no cambian el fd
		list = comm.parse_head;
		while (list)
		{
			if (((t_comm*)list->content)->post_pipe == 1)
			{
				page = ((t_comm*)list->content)->page;
				list = comm.parse_head;
				while (page == ((t_comm*)list->content)->page)
				{
					printf("pongo post\n");
					((t_comm*)list->content)->post_pipe = 1;
					list = list->next;
				}
			}
			if (((t_comm*)list->content)->prev_pipe == 1)
			{
				printf("prev: %s\n", ((t_comm*)list->content)->t_word);
				page = ((t_comm*)list->content)->page;
				while (list && page == ((t_comm*)list->content)->page)
				{
					((t_comm*)list->content)->prev_pipe = 1;
					if (((t_comm*)list->next->content)->t_pipe != 1)
						list = list->next;
				}
				printf("out: %s\n", ((t_comm*)list->content)->t_word);
			}
			//printf("out: %s\n", ((t_comm*)list->content)->t_word);
			//printf("--page %d\n", ((t_comm*)list->content)->page);
			list = list->next;
		}*/
		//test_list(list, &comm);
		list = comm.parse_head;
		i = 1;
		char *str;
		char *aux;
		int fdin;
		int fdout;     //TODO: todo estos fd a la estructura
		int real_fdout;
		int	real_fdin;
		int fd[2]; //TODO: habra que meterlo en la funcion correspondiente

		fdin = 0;
		fdout = 0;
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
		ft_lstclear(&comm.parse_head, &free_list);
		print_user(&comm);
	}
	return (0);
}
