/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:53:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/16 14:00:20 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_output(t_list **list, t_comm *comm, t_split *split, int *fd, int *fd_read)
{
	pid_t	pid;

	pid = fork();
	printf("he hecho fork output con %d\n", pid);
	if (pid == 0)
	{
		if (*fd_read)
		{
			dup2(*fd_read, STDIN_FILENO);
			close(*fd_read);
		}
		close(fd[0]);
		printf("output dentro: %s\n", ((t_comm *)(*list)->content)->t_word);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		fprintf(stderr, "ejecutamos output\n");
		fprintf(stderr, "fd out:%d\n", fd[1]);
		manage_redir(list, ((t_comm *)(*list)->content), split);
		exit(split->errorcode);
	}
	else if (pid < 0)
		ft_error(split, NULL, 9);
	split->pipe_wait++;
	if (*fd_read)
		close(*fd_read);
	*fd_read = fd[0];
	close(fd[1]);
}

void	pipe_input(t_list **list, t_comm *comm, t_split *split, int *fd_read)
{
	pid_t	pid;

	printf("detro input\n");
	pid = fork();
	printf("he hecho fork input con %d\n", pid);
	if (pid == 0)
	{
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		dup2(*fd_read, STDIN_FILENO);
		close(*fd_read);
		printf("ejecutamos input\n");
		fprintf(stderr, "fd in:%d\n", *fd_read);
		manage_redir(list, ((t_comm *)(*list)->content), split);
		exit(split->errorcode);
	}
	else if (pid < 0)
		ft_error(split, NULL, 9);
	split->pipe_wait++;
	split->last_pid = pid;
	close(*fd_read);
	*fd_read = 0;
}

void	wait_pipes(t_comm *comm, t_split *split)
{
	int	status;
	int	i;

	i = 0;
	printf("wait con %d\n", split->last_pid);
	waitpid(split->last_pid, &status, 0);
	split->errorcode = status >> 8;
	while (i < split->pipe_wait - 1)
	{
		printf("cerramos hijo\n");
		wait(NULL);
		i++;
	}
	split->pipe_wait = 0;
}