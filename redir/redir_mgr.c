/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mgr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:19:48 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 15:44:35 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chek_if_fd(t_list **list, t_comm *comm, t_split *split)
{
	if ((((*list)->next)
			&& ((((t_comm *)((*list)->next)->content)->t_semi) == 1
			|| (((t_comm *)((*list))->content)->post_pipe)))
		|| ((*list)->next) == NULL )
		return (1);
	return (0);
}

void	manage_redir_files(t_list **list, t_comm *comm, t_split *split)
{
	split->aux = split->str;
	if (((t_comm *)((*list)->content))->redir.rest)
	{
		split->str = ft_strjoin(split->str, ((t_comm *)((*list)
						->content))->redir.rest);
		free (split->aux);
	}
	if (comm->redir.fdout)
		close(comm->redir.fdout);
	if (comm->redir.fdin)
		close(comm->redir.fdin);
	if (((t_comm *)((*list)->content))->t_gt)
	{
		comm->redir.fdout = open(((t_comm *)((*list)->content))->redir.file,
				O_RDWR | O_TRUNC | O_CREAT, 0700);
	}
	if (((t_comm *)((*list)->content))->t_gtgt)
		comm->redir.fdout = open(((t_comm *)((*list)->content))->redir.file,
				O_RDWR | O_APPEND | O_CREAT, 0700);
}

void	manage_fd(t_list **list, t_comm *comm, t_split *split)
{
	if (comm->redir.fdout)
	{
		comm->redir.real_fdout = dup(1);
		dup2(comm->redir.fdout, 1);
	}
	if (comm->redir.fdin)
	{
		comm->redir.real_fdin = dup(0);
		dup2(comm->redir.fdin, 0);
	}
	if (comm->redir.fdin >= 0)
		parse_command(*list, comm, split);
	if (comm->redir.fdout)
	{
		close(comm->redir.fdout);
		dup2(comm->redir.real_fdout, 1);
		close (comm->redir.real_fdout);
	}
	if (comm->redir.fdin)
	{
		close(comm->redir.fdin);
		dup2(comm->redir.real_fdin, 0);
		close(comm->redir.real_fdin);
	}
}

void	check_fd(t_list **list, t_comm *comm, t_split *split)
{
	if (((t_comm *)((*list)->content))->t_word && !split->str)
		split->str = ft_strdup(((t_comm *)((*list)->content))->t_word);
	else if (!((t_comm *)((*list)->content))->t_word && split->str)
	{
		manage_redir_files(list, comm, split);
		if (((t_comm *)((*list)->content))->t_lt)
		{
			comm->redir.fdin = \
				open(((t_comm *)((*list)->content))->redir.file, O_RDONLY);
			if (comm->redir.fdin == -1)
				ft_error(split,
					((t_comm *)((*list)->content))->redir.file, 5);
		}
	}	
}

void	manage_redir(t_list **list, t_comm *comm, t_split *split)
{
	init_redir_mgr(comm, split);
	while (*list)
	{
		check_fd(list, comm, split);
		if (chek_if_fd(list, comm, split))
		{
			((t_comm *)((*list)->content))->t_command = ft_strdup(split->str);
			if (split->str)
				free(split->str);
			manage_fd(list, comm, split);
			if (((*list)->next)
				&& ((t_comm *)((*list)->content))->post_pipe == 0)
				*list = ((*list)->next);
			else
				break ;
		}
		if (((*list)->next) && ((t_comm *)((*list)->content))->t_semi == 0)
		{
			if (((t_comm *)((*list)->content))->t_pipe == 1)
				split->str = NULL;
			*list = ((*list)->next);
		}
		else
			return ;
	}
}
