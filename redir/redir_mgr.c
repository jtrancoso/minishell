/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mgr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:19:48 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/12 14:25:07 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_redir(t_list **list, t_comm *comm, t_split *split)
{
	char *str;
	char *aux;
	int fdin;
	int fdout;     //TODO: todo estos fd a la estructura
	int real_fdout;
	int	real_fdin;

	fdin = 0;
	fdout = 0;
	str = NULL;
	while ((((t_comm*)((*list)->content))->page) == comm->p_page)
	{
		printf("page: %d\n", comm->p_page);
		if (((t_comm*)((*list)->content))->t_word && !str)
			str = ft_strdup(((t_comm*)((*list)->content))->t_word);
		else if (!((t_comm*)((*list)->content))->t_word && str)
		{
			aux = str;
			if (((t_comm*)((*list)->content))->redir.rest)
			{
				str = ft_strjoin(str, ((t_comm*)((*list)->content))->redir.rest);
				free (aux);
			}
			if (fdout)
				close(fdout);
			if (fdin)
				close(fdin);
			if (((t_comm*)((*list)->content))->t_gt)
				fdout = open(((t_comm*)((*list)->content))->redir.file, O_RDWR | O_TRUNC | O_CREAT, 0700);
			if (((t_comm*)((*list)->content))->t_gtgt)
				fdout = open(((t_comm*)((*list)->content))->redir.file, O_RDWR | O_APPEND | O_CREAT, 0700);
			if (fdout)
				real_fdout = dup(1);
			if (((t_comm*)((*list)->content))->t_lt)
				fdin = open(((t_comm*)((*list)->content))->redir.file, O_RDONLY);
			if (fdin)
				real_fdin = dup(0);
		}
		if ((((*list)->next) && ((((t_comm*)((*list)->next)->content)->t_semi) == 1)) || !((*list)->next)) //FIXME: reevaluar uso de pages
		{
			((t_comm*)((*list)->content))->t_command = ft_strdup(str);
			if (str)
				free(str);
			if (fdout)
				dup2(fdout, 1);
			if (fdin)
				dup2(fdin, 0);
			parse_command(*list, comm, split);
			//test_list(list, &comm);
			if (fdout)
			{
				close(fdout);
				dup2(real_fdout, 1);
				close (real_fdout);
			}
			if (fdin)
			{
				close(fdin);
				dup2(real_fdin, 0);
				close(real_fdin);
			}
			comm->p_page++;
			if (((*list)->next))
				list = &((*list)->next);
		}
		if (((*list)->next) || ((t_comm*)((*list)->content))->page == 0)
		{
			if (((t_comm*)((*list)->content))->page == 0)
				str = NULL;
			list = &((*list)->next);
		}
	}
}