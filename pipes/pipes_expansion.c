/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:46:34 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/24 11:38:33 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	father_pipe_output(t_split *split, int *fd[2])
{
	close((*fd)[1]);
	split->last_fd = dup((*fd)[0]);
	close((*fd)[0]);
	split->pipe_wait++;
}

void	son_pipe_input_output(t_comm *comm, t_split *split)
{
	dup2(split->last_fd, 0);
	dup2(comm->redir.fdout, 1);
	close(comm->redir.fdout);
	close(split->last_fd);
}

void	father_pipe_input_output(t_split *split, int *fd[2])
{
	close((*fd)[1]);
	close(split->last_fd);
	split->last_fd = dup((*fd)[0]);
	close((*fd)[0]);
	split->pipe_wait++;
}

void	son_pipe_input(t_comm *comm, t_split *split)
{
	dup2(split->last_fd, 0);
	dup2(comm->redir.fdout, 1);
	close(split->last_fd);
	close(comm->redir.fdout);
}

void	father_pipe_input(t_split *split, pid_t pid)
{
	split->last_pid = pid;
	close(split->last_fd);
	split->pipe_wait++;
}
