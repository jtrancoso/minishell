/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mgr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:19:48 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/13 10:08:30 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_redir(t_list **list, t_comm *comm, t_split *split)
{
	char	*str;
	char	*aux;

	comm->redir.fdin = 0;
	comm->redir.fdout = 0;
	str = NULL;
	while ((((t_comm *)((*list)->content))->page) == comm->p_page)
	{
		printf("page: %d\n", comm->p_page);
		if (((t_comm *)((*list)->content))->t_word && !str)
			str = ft_strdup(((t_comm *)((*list)->content))->t_word);
		else if (!((t_comm *)((*list)->content))->t_word && str)
		{
			aux = str;
			if (((t_comm *)((*list)->content))->redir.rest)
			{
				str = ft_strjoin(str, ((t_comm *)((*list)->content))->redir.rest);
				free (aux);
			}
			if (comm->redir.fdout)
				close(comm->redir.fdout);
			if (comm->redir.fdin)
				close(comm->redir.fdin);
			if (((t_comm *)((*list)->content))->t_gt)
				comm->redir.fdout = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDWR
						| O_TRUNC | O_CREAT, 0700);
			if (((t_comm *)((*list)->content))->t_gtgt)
				comm->redir.fdout = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDWR
						| O_APPEND | O_CREAT, 0700);
			if (comm->redir.fdout)
				comm->redir.real_fdout = dup(1);
			if (((t_comm *)((*list)->content))->t_lt)
				comm->redir.fdin = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDONLY);
			if (comm->redir.fdin)
				comm->redir.real_fdin = dup(0);
		}
		if ((((*list)->next)
			&& ((((t_comm *)((*list)->next)->content)->t_semi) == 1))
			|| !((*list)->next)) //FIXME: reevaluar uso de pages
		{
			((t_comm *)((*list)->content))->t_command = ft_strdup(str);
			if (str)
				free(str);
			if (comm->redir.fdout)
				dup2(comm->redir.fdout, 1);
			if (comm->redir.fdin)
				dup2(comm->redir.fdin, 0);
			parse_command(*list, comm, split);
			//test_list(list, &comm);
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
			comm->p_page++;
			if (((*list)->next))
				list = &((*list)->next);
		}
		if (((*list)->next) || ((t_comm *)((*list)->content))->page == 0)
		{
			if (((t_comm *)((*list)->content))->page == 0)
				str = NULL;
			list = &((*list)->next);
		}
	}
}
