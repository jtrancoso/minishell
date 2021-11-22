/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:48:23 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/22 12:48:34 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_parse_quote(t_split *split)
{
	split->i = 0;
	split->s_quote = 0;
	split->d_quote = 0;
}

void	check_if_quotes(t_split *split, char *line)
{
	if ((line[split->i] == '\\' && line[split->i + 1] == '\"')
		|| (line[split->i] == '\\' && line[split->i + 1] == '\''
			&& split->s_quote % 2 == 0))
		split->i += 1;
	else if (line[split->i] == '\\' && line[split->i + 1] == '\''
		&& split->s_quote % 2 != 0)
	{
		split->i++;
		split->s_quote++;
	}
	else if (line[split->i] == '\"' && split->s_quote % 2 == 0)
		split->d_quote++;
	else if (line[split->i] == '\'' && split->d_quote % 2 == 0)
		split->s_quote++;
}

int	ft_parse_quote(t_comm *comm, t_split *split, char *line)
{
	init_parse_quote(split);
	while (line[split->i])
	{
		if (split->i == 0 && line[split->i] == '\\'
			&& (line[split->i + 1] == '\"' || line[split->i + 1] == '\''))
			split->i += 1;
		else
			check_if_quotes(split, line);
		split->i++;
	}
	if (split->s_quote % 2 != 0 || split->d_quote % 2 != 0)
		return (ft_error(split, NULL, 1));
	return (0);
}