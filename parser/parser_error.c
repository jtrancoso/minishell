/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:16:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/27 13:21:01 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_command(t_comm *comm, t_split *split, char *line)
{
	printf("hola");
	return (0);
}

int parser_error(t_comm *comm, t_split *split, char *line, char *mode)
{
	int i;

	i = 0;
	if (ft_strncmp(mode, "syntax", 6) == 0)
	{
		if (line[0] == ';' || line[0] == '|' || line[0] == '<')
			return(ft_error(split, 3));
		while(line[i])
		{
			if (line[i] == '<' && line[i + 1] == '<' && line[i + 1] != '\0')
				return(ft_error(split, 3));
			else if (line[i] == ';' && line[i + 1] == ';' && line[i + 1] != '\0')
				return(ft_error(split, 3));
			else if (line[i] == '|' && line[i + 1] == '|' && line[i + 1] != '\0')
				return(ft_error(split, 3));
			i++;
		}
	}
	if (ft_strncmp(mode, "comand", 6) == 0)
	{
		check_command(comm, split, line);
	}
	return (0);
}