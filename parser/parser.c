/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/04/09 13:49:39 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_quote(t_comm *comm, char *line)
{
	int s_quote;
	int d_quote;
	int i;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i])
	{
		if (line[i] == '"')
			d_quote++;
		if (line[i] == '\'')
			s_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		ft_error(1);
}

int	ft_parseline(t_comm *comm, char *line)
{
	int		i;
	char	aux[BUFFERSIZE];
	int		j;

	i = 0;
	j = 0;
	ft_bzero(aux, BUFFERSIZE - 1);
	while (ft_isspace(line[i]))
		i++;
	ft_parse_quote(comm, line + i);
	while (ft_isascii(line[i]))
	{
		aux[j] = line[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	while (ft_isspace(line[i]))
		i++;
	//printf("iii\n");
	if (ft_strncmp(aux, "echo", 4) == 0)
	{
		//printf("1123\n");
		printf("%s\n", line + i);
		return (ft_echo(comm, line + i));
	}
	return (0);
}
