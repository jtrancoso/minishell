/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:06:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/20 18:40:26 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipes(t_list **list, t_comm *comm, t_split *split, int *fd)
{
	if (((t_comm *)(*list)->content)->post_pipe)
		pipe(fd);
	if (((t_comm *)(*list)->content)->post_pipe == 0
		&& ((t_comm *)(*list)->content)->prev_pipe == 0
		&& ((t_comm *)(*list)->content)->t_pipe == 0
		&& ((t_comm *)(*list)->content)->prev_redir == 0)
		manage_redir(list, comm, split);
	if (((t_comm *)(*list)->content)->prev_pipe == 0
		&& ((t_comm *)(*list)->content)->post_pipe == 1
		&& ((t_comm *)(*list)->content)->t_word != NULL)
		pipe_output(list, comm, split, &fd);
	if (((t_comm *)(*list)->content)->prev_pipe == 1
		&& ((t_comm *)(*list)->content)->post_pipe == 1
		&& ((t_comm *)(*list)->content)->t_word != NULL)
		pipe_input_output(list, comm, split, &fd);
	if (((t_comm *)(*list)->content)->prev_pipe == 1
		&& ((t_comm *)(*list)->content)->post_pipe == 0
		&& ((t_comm *)(*list)->content)->t_word != NULL)
	{
		pipe_input(list, comm, split, &fd);
		wait_pipes(comm, split);
		split->pipe_wait = 0;
	}
}
