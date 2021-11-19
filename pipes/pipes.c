/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:53:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/19 09:19:45 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_output(t_list **list, t_comm *comm, t_split *split, int *fd[2])
{
	pid_t	pid;

	pid = fork();
	////fprintf(stderr, "he hecho fork out con %d\n", pid);
	if (!pid)
	{
		close((*fd)[0]);
		dup2((*fd)[1], 1);
		close((*fd)[1]);
		////fprintf(stderr, "hijo de output\n");
		//parse_command(*list, comm, split);
		manage_redir(list, comm, split);
		exit(split->errorcode);	//TODO: comprobar exit code
	}
	else
	{
		////fprintf(stderr, "padre de output\n");
		close((*fd)[1]);
		split->last_fd = dup((*fd)[0]); //TODO: mirar si es necesario
		////fprintf(stderr, "last fd en out: %d\n", split->last_fd);
		close((*fd)[0]);
		split->pipe_wait++;
	}
}

void	pipe_input_output(t_list **list, t_comm *comm, t_split *split,
	int *fd[2])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		close((*fd)[0]);
		dup2(split->last_fd, 0);
		close(split->last_fd);
		dup2((*fd)[1], 1);
		close ((*fd)[1]);
		//parse_command(*list, comm, split);
		manage_redir(list, comm, split);
		exit(split->errorcode);	//TODO: comprobar exit code
	}
	else
	{
		////fprintf(stderr, "padre de output e input\n");
		close((*fd)[1]);
		close(split->last_fd);
		split->last_fd = dup((*fd)[0]); //TODO: mirar si es necesario
		close((*fd)[0]);
		split->pipe_wait++;
	}
}

void	pipe_input(t_list **list, t_comm *comm, t_split *split, int *fd[2])
{
	pid_t	pid;

	(void)fd;
	pid = fork();
	//fprintf(stderr, "he hecho fork input con %d\n", pid);
	if (!pid)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, default_sigquit);
		//fprintf(stderr, "last fd en input: %d\n", split->last_fd);
		dup2(split->last_fd, 0);
		close(split->last_fd);
		//fprintf(stderr, "hijo de intput\n");
		//parse_command(*list, comm, split);
		manage_redir(list, comm, split);
		exit(split->errorcode);	//TODO: comprobar exit code
	}
	else
	{
		//fprintf(stderr, "padre de intput\n");
		split->last_pid = pid;
		close(split->last_fd);
		split->pipe_wait++;
	}
}

void	wait_pipes(t_comm *comm, t_split *split)
{
	int status;
	int i;

	if (split->pipe_wait > 0)
	{
		//fprintf(stderr, "esperamos a pid: %d\n", split->last_pid);
		waitpid(split->last_pid, &status, 0);
		i = 0;
		while (++i < split->pipe_wait)
			wait(NULL);
		split->errorcode = status >> 8;
	}
}
