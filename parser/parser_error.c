/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:16:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/23 13:41:08 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char *line, int *i)
{
	int	j;

	if (line[*i] == '>' && (ft_isspace(line[*i + 1])))
	{
		j = *i + 1;
		while (ft_isspace(line[j]))
			j++;
		if (line[j] == '<' || line[j] == '>')
			return (1);
	}
	if (line[*i] == '<' && (ft_isspace(line[*i + 1])))
	{
		j = *i + 1;
		while (ft_isspace(line[j]))
			j++;
		if (line[j] == '<' || line[j] == '>')
			return (1);
	}
	return (0);
}

int	check_redir_syntax(char *line, int *i)
{
	int	j;
	int	l;

	j = 0;
	l = *i;
	while (line[l] == '>')
	{
		l++;
		j++;
	}
	if (j > 2)
		return (1);
	if (check_spaces(line, i))
		return (1);
	if (line[*i] == '<' && line[*i + 1] == '<' && line[*i + 1] != '\0')
		return (1);
	else if (line[*i] == '<' && line[*i + 1] == '>' && line[*i + 1] != '\0')
		return (1);
	else if (line[*i] == '>' && line[*i + 1] == '<' && line[*i + 1] != '\0')
		return (1);
	else if (line[*i] == '>' && line[*i + 1] == '>' && line[*i + 2] == '\0')
		return (1);
	return (0);
}

int	parser_error_bis(t_split *split, char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i]));
	else if (line[*i] == '|' && line[*i + 1] == ';' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i + 1]));
	else if (line[*i] == '<' || line[*i] == '>')
	{
		if (check_redir_syntax(line, i))
			return (ft_error_syntax(split, line[*i]));
	}
	else if ((line[*i] == '|' || line[*i] == ';')
		&& line[*i + 1] == ' ' && line[*i + 2])
	{
		*i += 1;
		while (ft_isspace(line[*i]))
			*i += 1;
		if (!ft_isalnum(line[*i]))
			return (ft_error_syntax(split, line[*i]));
	}
	return (0);
}

int	parser_error(t_split *split, char *line)
{
	int	i;

	i = 0;
	if (line[0] == ';' || line[0] == '|' || line[0] == '<' || line[0] == '>')
		return (ft_error_syntax(split, line[0]));
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';' && line[i + 1] != '\0')
			return (ft_error_syntax(split, line[i]));
		else if (line[i] == ';' && i > 0 && (line[i - 1] == '<'
				|| line[i - 1] == '>'))
			return (ft_error_syntax(split, line[i]));
		else if (line[i] == ';' && line[i + 1] == '|' && line[i + 1] != '\0')
			return (ft_error_syntax(split, line[i]));
		else if (parser_error_bis(split, line, &i))
			return (1);
		i++;
	}
	if ((line[i - 1] == '<' || line[i - 1] == '>'
			|| line[i - 1] == '|') && i > 0)
		return (ft_error_syntax(split, line[i]));
	return (0);
}
