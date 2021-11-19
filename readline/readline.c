/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:55:45 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/19 16:05:09 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_line(t_comm *comm, t_line *line)
{
	while (1)
	{
		line->char_read[1] = '\0';
		if (!comm->final_line)
			comm->final_line = ft_strdup(line->char_read);
		else
		{
			if (line->bit_read == 0 && !line->join_line)
				line->join_line = ft_strdup(comm->final_line);
			line->tmp = comm->final_line;
			comm->final_line = ft_strjoin(comm->final_line, line->char_read);
			free(line->tmp);
		}
		if (comm->final_line[line->i] == '\n')
		{
			if (line->join_line)
			{
				free(comm->final_line);
				comm->final_line = line->join_line;
			}
			break ;
		}
		line->i++;
		line->bit_read = read(0, line->char_read, 1);
	}
}

void	our_read_line(t_comm *comm, t_split *split)
{
	t_line	line;

	split->pars = 0;
	line.i = 0;
	line.join_line = NULL;
	line.bit_read = read(0, line.char_read, 1);
	if (line.bit_read == 0)
		ctrl_d(split);
	fill_line(comm, &line);
}
