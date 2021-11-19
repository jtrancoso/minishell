/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:06:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/19 09:17:12 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipes(t_list **list, t_comm *comm, t_split *split, int *fd)
{
	if (((t_comm *)(*list)->content)->post_pipe)
	{
		//fprintf(stderr, "abro pipe\n");
		pipe(fd);
	}
	//split->fd_out = dup(1);
	//split->fd_in = dup(0);
	if (((t_comm *)(*list)->content)->post_pipe == 0
		&& ((t_comm *)(*list)->content)->prev_pipe == 0
		&& ((t_comm *)(*list)->content)->t_pipe == 0)
	{
		//parse_command(*list, comm, split);
		manage_redir(list, comm, split);
		wait_pipes(comm, split);
		split->pipe_wait = 0;
		//fprintf(stderr, "hemos hecho un simple\n");
	}
	if (((t_comm *)(*list)->content)->prev_pipe == 0
		&& ((t_comm *)(*list)->content)->post_pipe == 1
		&& ((t_comm *)(*list)->content)->t_word != NULL) //TODO: lo mismo no hace falta el word
	{
		//fprintf(stderr, "hacemos output: %s\n", ((t_comm*)(*list)->content)->t_word);
		pipe_output(list, comm, split, &fd);
	}
	if (((t_comm *)(*list)->content)->prev_pipe == 1
		&& ((t_comm *)(*list)->content)->post_pipe == 1
		&& ((t_comm *)(*list)->content)->t_word != NULL)
	{
		//fprintf(stderr, "hacemos el pipe doble con: %s\n", ((t_comm*)(*list)->content)->t_word);
		pipe_input_output(list, comm, split, &fd);
	}
	if (((t_comm *)(*list)->content)->prev_pipe == 1
		&& ((t_comm *)(*list)->content)->post_pipe == 0
		&& ((t_comm *)(*list)->content)->t_word != NULL)
	{
		//fprintf(stderr, "He llegado al input\n");
		pipe_input(list, comm, split, &fd);
		//fprintf(stderr, "me espero\n");
		wait_pipes(comm, split); //TODO:si no funciona, se sube
		split->pipe_wait = 0;
	}
	/*if (split->last_pid && (((t_comm*)(*list)->content)->next_semi == 1 || !(*list)->next))
	{
		//fprintf(stderr, "me espero\n");
		wait_pipes(comm, split); //TODO:si no funciona, se sube
		split->pipe_wait = 0;
	}*/
	//dup2(split->fd_out, 1);
	//dup2(split->fd_in, 0);
	//close(split->fd_out);
}
