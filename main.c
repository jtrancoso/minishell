/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/20 19:46:18 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miraleaks(void)
{
	system("leaks minishell");
}

void	execute_things(t_list *list, t_comm *comm, t_split *split)
{
	int	*fd;

	list = comm->parse_head;
	split->pipe_wait = 0;
	fd = ft_malloc(sizeof(int) * 2);
	while (list)
	{
		split->last_pid = 0;
		if (((t_comm *)list->content)->t_gt == 0
			&& ((t_comm *)list->content)->t_lt == 0
			&& ((t_comm *)list->content)->t_gtgt == 0)
			execute_pipes(&list, comm, split, fd);
		list = list->next;
	}
	free(fd);
}

void	init_main(t_comm *comm, char **argv, int argc, char **envp)
{
	(void)argv;
	(void)argc;
	print_prompt(comm);
	check_env(comm, envp);
}

void	execute_loop(t_list *list, t_comm *comm, t_split *split)
{
	parse_redir(list, comm, split);
	set_flags(list, comm);
	//test_list(list, comm);
	execute_things(list, comm, split);
	ft_lstclear(&comm->parse_head, &free_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;
	t_comm	comm;
	t_split	split;

	//atexit(miraleaks);
	list = NULL;
	init_main(&comm, argv, argc, envp);
	set_shlvl(list, &comm, &split);
	while (1)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, default_sigquit);
		our_read_line(&comm, &split);
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		split.pars = ft_parseline(&comm, &split, NULL);
		free(comm.final_line);
		comm.final_line = NULL;
		if (!split.pars)
			execute_loop(list, &comm, &split);
		print_user(&comm);
	}
	return (0);
}
