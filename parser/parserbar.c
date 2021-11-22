/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:45:15 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/22 10:04:59 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_bar(t_split *split)
{
	split->i = 0;
	split->bar = 0;
	split->s_quote = 0;
	split->d_quote = 0;
}

int	check_bars(t_split *split, char *line)
{
	if (split->d_quote % 2 != 0 && line[split->i] == '\"'
		&& line[split->i - 1] != '\\')
		split->d_quote++;
	else if (split->d_quote % 2 != 0 && line[split->i] == '\"'
		&& line[split->i - 1] == '\\')
		split->i++;
	else if (split->s_quote % 2 != 0)
		split->s_quote++;
	else if (line[split->i] == '\\' && line[split->i + 1])
		split->i++;
	else if (line[split->i] == '\\' && line[split->i + 1] == '\0')
		return (ft_error(split, NULL, 7));
	return (0);
}

int	ft_parse_bar(t_comm *comm, t_split *split, char *line)
{
	init_bar(split);
	while (line[split->i])
	{
		if (split->aux == 0)
		{
			if (line[split->i] == '\'')
				split->s_quote++;
			else if (line[split->i] == '\"')
				split->d_quote++;
			else if (line[split->i] == '\\')
			{
				if (line[split->i + 1] != '\0')
					split->i++;
				else
					return (ft_error(split, NULL, 7));
			}
		}
		else if (split->i > 0)
			check_bars(split, line);
		split->i++;
	}
	if (split->bar % 2 != 0)
		return (ft_error(split, NULL, 7));
	else
		return (0);
}
