/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:53:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 10:39:35 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_output(t_list **list, t_comm *comm, t_split *split, int *fd[2])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		close((*fd)[0]);
		if (comm->redir.fdout > 0)
		{
			dup2(comm->redir.fdout, 1);
			close(comm->redir.fdout);
			close((*fd)[1]);
		}
		else
		{
			dup2((*fd)[1], 1);
			close((*fd)[1]);
		}
		if (((t_comm *)(*list)->content)->prev_redir == 0)
			manage_redir(list, comm, split);
		exit(split->errorcode);
	}
	else
		father_pipe_output(split, fd);
}

void	pipe_input_output(t_list **list, t_comm *comm, t_split *split,
	int *fd[2])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		close((*fd)[0]);
		if (comm->redir.fdout > 0)
			son_pipe_input_output(comm, split);
		else
		{
			dup2(split->last_fd, 0);
			close(split->last_fd);
			dup2((*fd)[1], 1);
		}
		close ((*fd)[1]);
		if (((t_comm *)(*list)->content)->prev_redir == 0)
			manage_redir(list, comm, split);
		exit(split->errorcode);
	}
	else
		father_pipe_input_output(split, fd);
}

void	pipe_input(t_list **list, t_comm *comm, t_split *split, int *fd[2])
{
	pid_t	pid;

	(void)fd;
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, default_sigquit);
		if (comm->redir.fdout > 0)
			son_pipe_input(comm, split);
		else
		{
			dup2(split->last_fd, 0);
			close(split->last_fd);
		}
		if (((t_comm *)(*list)->content)->prev_redir == 0)
			manage_redir(list, comm, split);
		exit(split->errorcode);
	}
	else
		father_pipe_input(split, pid);
}

void	wait_pipes(t_split *split)
{
	int	status;
	int	i;

	if (split->pipe_wait > 0)
	{
		waitpid(split->last_pid, &status, 0);
		i = 0;
		while (++i < split->pipe_wait)
			wait(NULL);
		split->errorcode = status >> 8;
	}
}
