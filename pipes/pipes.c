/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:53:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/15 19:57:47 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_output(t_list **list, t_comm *comm, t_split *split, int *fd, int *fd_read)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (*fd_read)
		{
			dup2(*fd_read, 0);
			close(*fd_read);
		}
		close(fd[0]);
		printf("output dentro: %s\n", ((t_comm *)(*list)->content)->t_word);
		dup2(fd[1], 1);
		close(fd[1]);
		manage_redir(list, comm, split);
		exit(split->errorcode);
	}
	else if (pid < 0)
		ft_error(split, NULL, 9);
	comm->pipe_wait++;
	if (*fd_read)
		close(*fd_read);
	*fd_read = fd[0];
	close(fd[1]);
}

void	pipe_input(t_list **list, t_comm *comm, t_split *split, int *fd_read)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		dup2(*fd_read, 0);
		close(*fd_read);
		manage_redir(list, comm, split);
		exit(split->errorcode);
	}
	else if (pid < 0)
		ft_error(split, NULL, 9);
	comm->pipe_wait++;
	comm->last_pid = pid;
	close(*fd_read);
	*fd_read = 0;
}

void	wait_pipes(t_comm *comm, t_split *split)
{
	int	status;
	int	i;

	i = 0;
	waitpid(comm->last_pid, &status, 0);
	split->errorcode = status >> 8;
	while (i < comm->pipe_wait - 1)
	{
		wait(NULL);
		i++;
	}
	comm->pipe_wait = 0;
}