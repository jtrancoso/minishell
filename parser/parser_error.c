/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:16:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/16 10:43:19 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_error_bis(t_comm *comm, t_split *split, char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|' && line[*i + 1] != '\0')
		return (ft_error(split, NULL, 3));
	else if (line[*i] == '<' && line[*i + 1] == '>' && line[*i + 1] != '\0')
		return (ft_error(split, NULL, 3));
	else if (line[*i] == '>' && line[*i + 1] == '<' && line[*i + 1] != '\0')
		return (ft_error(split, NULL, 3));
	else if (line[*i] == '<' && line[*i + 1] == '<' && line[*i + 1] != '\0')
		return (ft_error(split, NULL, 3));
	/*else if (line[*i] == '>' && line[*i + 1] == '>' && line[*i + 2] == '>' && line[*i + 3] != '\0')
		return (ft_error(split, NULL, 3));*/
	else if ((line[*i] == '|' || line[*i] == ';')
		&& line[*i + 1] == ' ' && line[*i + 2])
	{
		*i += 1;
		while (ft_isspace(line[*i]))
			*i += 1;
		if (!ft_isalnum(line[*i]))
			return (ft_error(split, NULL, 3));
	}
	return (0);
}

int	parser_error(t_comm *comm, t_split *split, char *line) //TODO: añadir errores cuando el caracter especial acaba la linea
{
	int	i;

	i = 0;
	if (line[0] == ';' || line[0] == '|' || line[0] == '<')
		return (ft_error(split, NULL, 3));
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';' && line[i + 1] != '\0')
			return (ft_error(split, NULL, 3));
		else if (line[i] == ';' && line[i + 1] == '|' && line[i + 1] != '\0')
			return (ft_error(split, NULL, 3));
		else
			parser_error_bis(comm, split, line, &i);
		i++;
	}
	if ((line[i - 1] == '<' || line[i - 1] == '>'
			|| line[i - 1] == '|') && i > 0)
		return (ft_error(split, NULL, 3));
	return (0);
}
