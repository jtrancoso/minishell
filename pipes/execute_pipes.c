/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:06:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 09:44:23 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(t_list *list)
{
	while (list)
	{
		if (((t_comm *)(list)->content)->post_pipe)
			return (1);
		list = (list)->next;
	}
	return (0);
}

int	checkif_pipeoutput(t_list **list)
{
	if (((t_comm *)(*list)->content)->prev_pipe == 0
		&& ((t_comm *)(*list)->content)->post_pipe == 1
		&& ((t_comm *)(*list)->content)->t_word != NULL)
		return (1);
	return (0);
}

int	checkif_pipe_input_output(t_list **list)
{
	if (((t_comm *)(*list)->content)->prev_pipe == 1
		&& ((t_comm *)(*list)->content)->post_pipe == 1
		&& ((t_comm *)(*list)->content)->t_word != NULL)
		return (1);
	return (0);
}

int	checkif_pipe_input(t_list **list)
{
	if (((t_comm *)(*list)->content)->prev_pipe == 1
		&& ((t_comm *)(*list)->content)->post_pipe == 0
		&& ((t_comm *)(*list)->content)->t_word != NULL)
		return (1);
	return (0);
}

void	execute_pipes(t_list **list, t_comm *comm, t_split *split, int *fd)
{
	if (split->pipe_n > 0 && (((t_comm *)(*list)->content)->post_pipe
		|| check_pipes(*list)))
	{
		pipe(fd);
		split->pipe_n--;
	}
	if (((t_comm *)(*list)->content)->post_pipe == 0
		&& ((t_comm *)(*list)->content)->prev_pipe == 0
		&& ((t_comm *)(*list)->content)->t_pipe == 0
		&& ((t_comm *)(*list)->content)->prev_redir == 0)
		manage_redir(list, comm, split);
	if (checkif_pipeoutput(list))
		pipe_output(list, comm, split, &fd);
	if (checkif_pipe_input_output(list))
		pipe_input_output(list, comm, split, &fd);
	if (checkif_pipe_input(list))
	{
		pipe_input(list, comm, split, &fd);
		wait_pipes(split);
		split->pipe_wait = 0;
	}
}
