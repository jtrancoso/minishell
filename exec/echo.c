/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:15:19 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 09:14:54 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_printhome(t_list *list, t_comm *comm)
{
	comm->home = NULL;
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "HOME", 4) == 0)
			comm->home = ft_strdup(((t_env *)list->content)->value);
		list = list->next;
	}
	return (comm->home);
}

void	find_echon(t_comm *comm, int *i, int *j, size_t *l)
{
	int	q;

	q = 1;
	while (comm->cmd.cmd[q])
		q++;
	while (*i < q && (ft_strncmp(comm->cmd.cmd[*i], "-n", 2) == 0))
	{
		*j = 1;
		*l = 1;
		while (comm->cmd.cmd[*i][*j] == 'n')
		{
			*l += 1;
			*j += 1;
		}
		if (*l == ft_strlen(comm->cmd.cmd[*i]))
		{
			comm->flag_n = 1;
			*i += 1;
		}
		else
			break ;
	}
}

void	print_echo(t_list *list, t_comm *comm, int *i)
{
	int	j;

	j = 0;
	while (comm->cmd.cmd[*i][j])
	{
		if ((j == 0 && comm->cmd.cmd[*i][j] == '~'
			&& comm->cmd.cmd[*i][j + 1] == '/')
			|| (j == 0 && comm->cmd.cmd[*i][j] == '~'
			&& comm->cmd.cmd[*i][j + 1] == '\0' && comm->f_verg == 0))
		{
			ft_putstr_fd(ft_printhome(list, comm), 1);
			free(comm->home);
		}
		else
			ft_putchar_fd(comm->cmd.cmd[*i][j], 1);
		j++;
	}
	if (comm->cmd.cmd[*i + 1])
		ft_putchar_fd(' ', 1);
}

int	ft_echo(t_list *list, t_comm *comm)
{
	int		i;
	int		j;
	size_t	l;

	i = 1;
	comm->flag_n = 0;
	find_echon(comm, &i, &j, &l);
	while (comm->cmd.cmd[i])
	{
		print_echo(list, comm, &i);
		i++;
	}
	if (!comm->flag_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
