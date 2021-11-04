/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:16:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/04 11:02:37 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parser_error(t_comm *comm, t_split *split, char *line) //TODO: añadir errores cuando el caracter especial acaba la linea
{
	int i;

	i = 0;
	if (line[0] == ';' || line[0] == '|' || line[0] == '<')
		return(ft_error(split, 3));
	while(line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == ';' && line[i + 1] == '|' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == '|' && line[i + 1] == ';' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == '|' && line[i + 1] == '|' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == '<' && line[i + 1] == '>' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == '>' && line[i + 1] == '<' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == '<' && line[i + 1] == '<' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if ((line[i] == '|' || line[i] == ';') && line[i + 1] == ' ' && line[i + 2])
		{
			i++;
			while(ft_isspace(line[i]))
				i++;
			if (!ft_isalnum(line[i]))
				return(ft_error(split, 3));
		}
		i++;
	}
	if ((line[i - 1] == '<' || line[i - 1] == '>' || line[i - 1] == '|') && i > 0)
		return(ft_error(split, 3));
	return (0);
}