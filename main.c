/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/20 17:32:50 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miraleaks(void)
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

void	set_flags(t_list *list, t_comm *comm)
{
	list = comm->parse_head;
	while (list)
	{
		if (((t_comm *)list->content)->t_word != NULL && list->next)
		{
			if (((t_comm *)list->next->content)->t_pipe == 1)
				((t_comm *)list->content)->post_pipe = 1;
			if (((t_comm *)list->next->content)->t_semi == 1)
				((t_comm *)list->content)->next_semi = 1;
		}
		if (((t_comm *)list->content)->t_gt == 1
			|| ((t_comm *)list->content)->t_lt == 1
			|| ((t_comm *)list->content)->t_gtgt == 1)
			((t_comm *)list->next->content)->prev_redir = 1;
		if (((t_comm *)list->content)->t_pipe == 1)
		{
			if (((t_comm *)list->next->content)->t_word != NULL)
				((t_comm *)list->next->content)->prev_pipe = 1;
		}
		list = list->next;
	}
}

void	set_shlvl(t_list *list, t_comm *comm, t_split *split)
{
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "USER", 4) == 0)
			comm->user = ft_strdup(((t_env *)list->content)->value);
		else if (ft_strncmp(((t_env *)list->content)->id, "SHLVL", 5) == 0)
			((t_env *)list->content)->value
				= next_shlvl(((t_env *)list->content)->value);
		list = list->next;
	}
	split->errorcode = 0;
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
		if (((t_comm *)list->content)->t_gt == 0 && ((t_comm *)list->content)->t_lt == 0 && ((t_comm *)list->content)->t_gtgt == 0)
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
