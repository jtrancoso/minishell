/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:06:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/23 13:20:53 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(t_list *list, t_comm *comm)
{
	while (list)
	{
		if (((t_comm *)(list)->content)->post_pipe)
			return (1);
		list = (list)->next;
	}
	return (0);
}

void	execute_pipes(t_list **list, t_comm *comm, t_split *split, int *fd)
{
	if (check_pipes(*list, comm))
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
