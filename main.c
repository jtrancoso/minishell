/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/13 10:41:32 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miraleaks()
{
	system("leaks minishell");
}

void	check_env(t_comm *comm, char **envp)
{
	t_list	*new;
	t_env	*env;
	int		i;
	char	**split_env;

	i = 0;
	comm->env_head = NULL;
	if (!envp[i])
		galactic_env(comm);
	i = 0;
	while (envp[i])
	{
		new = ft_malloc(sizeof(t_list));
		env = ft_malloc(sizeof(t_env));
		split_env = ft_split(envp[i], '=');
		new->content = env;
		((t_env *)new->content)->id = split_env[0];
		((t_env *)new->content)->value = split_env[1];
		ft_lstadd_back(&comm->env_head, new);
		free(split_env);
		i++;
	}
}

int	main(int argv, char **argc, char **envp)
{
	t_list	*list;
	t_list	*new;
	t_env	*env;
	t_comm	comm;
	t_split	split;
	int		i;

	//atexit(miraleaks);
	print_prompt(&comm);
	check_env(&comm, envp);
	list = comm.env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "USER", 4) == 0)
			comm.user = ft_strdup(((t_env *)list->content)->value);
		else if (ft_strncmp(((t_env *)list->content)->id, "SHLVL", 5) == 0)
			((t_env *)list->content)->value = next_shlvl(((t_env *)list->content)->value);
		list = list->next;
	}
	split.errorcode = 0;
	int	pars;//para gestionar el error de sintaxis y que no libere
	while (1)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, default_sigquit);
		our_read_line(&comm, &split);
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		pars = ft_parseline(&comm, &split, NULL);
		free(comm.final_line);
		comm.final_line = NULL;
		list = comm.parse_head;
		//printf("1: %s\n", ((t_comm*)list->content)->t_word);
		i = 1;
		while (list)
		{
			if (((t_comm *)list->content)->t_pipe == 0 || ((t_comm *)list->content)->t_semi == 0)
				((t_comm *)list->content)->page = i;
			if (((t_comm *)list->content)->t_pipe == 1 || ((t_comm *)list->content)->t_semi == 1)
			{
				((t_comm *)list->content)->page = 0;
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
			if (((t_comm *)list->content)->t_word != NULL && list->next)
			{
				if (((t_comm *)list->next->content)->t_pipe == 1)
					((t_comm *)list->content)->post_pipe = 1;
			}
			if (((t_comm *)list->content)->t_pipe == 1)
			{
				if (((t_comm *)list->next->content)->t_word != NULL)
					((t_comm *)list->next->content)->prev_pipe = 1;
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
		int fd[2]; //TODO: habra que meterlo en la funcion correspondiente
		comm.p_page = 1;
		while (list)
		{
			if (((t_comm *)list->content)->post_pipe == 0 && ((t_comm *)list->content)->prev_pipe == 0)
				manage_redir(&list, &comm, &split);
			else
				printf("pillamos los pipes\n");
			list = list->next;
		}
		if (!pars)
			ft_lstclear(&comm.parse_head, &free_list);
		print_user(&comm);
	}
	return (0);
}
