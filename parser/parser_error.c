/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:16:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/19 17:30:50 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_error_bis(t_comm *comm, t_split *split, char *line, int *i) //TODO: falta gestionar los errores que nos dijo ramon
{
	if (line[*i] == '|' && line[*i + 1] == '|' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i]));
	else if (line[*i] == '|' && line[*i + 1] == ';' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i + 1]));
	else if (line[*i] == '<' && line[*i + 1] == '>' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i]));
	else if (line[*i] == '>' && line[*i + 1] == '<' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i]));
	else if (line[*i] == '<' && line[*i + 1] == '<' && line[*i + 1] != '\0')
		return (ft_error_syntax(split, line[*i]));
	else if (line[*i] == '>' && line[*i + 1] == '>' && line[*i + 2] == '\0')
		return (ft_error_syntax(split, line[*i]));
	/*else if (line[*i] == '>' && line[*i + 1] == '>' && line[*i + 2] == '>' && line[*i + 3] != '\0')
		return (ft_error(split, NULL, 3));*/
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

int	parser_error(t_comm *comm, t_split *split, char *line)
{
	int	i;

	i = 0;
	if (line[0] == ';' || line[0] == '|' || line[0] == '<' || line[0] == '>')
		return (ft_error_syntax(split, line[0]));
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';' && line[i + 1] != '\0')
			return (ft_error_syntax(split, line[i]));
		else if (line[i] == ';' && line[i + 1] == '|' && line[i + 1] != '\0')
			return (ft_error_syntax(split, line[i]));
		else if (parser_error_bis(comm, split, line, &i))
			return (1);
		i++;
	}
	if ((line[i - 1] == '<' || line[i - 1] == '>'
			|| line[i - 1] == '|') && i > 0)
		return (ft_error_syntax(split, line[i]));
	return (0);
}
