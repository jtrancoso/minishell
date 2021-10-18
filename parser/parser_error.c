/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:16:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/18 14:30:33 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parser_error(t_comm *comm, t_split *split, char *line)
{
	int i;

	i = 0;
	if (line[0] == ';' || line[0] == '|' || line[0] == '<')
		return(ft_error(split, 3));
	while(line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		else if (line[i] == '|' && line[i + 1] == '|' && line[i + 1] != '\0')
			return(ft_error(split, 3));
		i++;
	}
	return (0);
}