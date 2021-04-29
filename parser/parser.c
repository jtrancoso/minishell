/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/04/29 13:19:33 by jtrancos         ###   ########.fr       */
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
		if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			i += 2;
		if (line[i] == '\"' && s_quote % 2 == 0)
			d_quote++;
		if (line[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		ft_error(1);
}

int	ft_parseline(t_comm *comm, t_split *split, char *line)
{
	int		i;
	char	aux[BUFFERSIZE];
	int		j;
	t_list *head;
	t_list *list;
	t_list *new;

	i = 0;
	j = 0;
	line[ft_strlen(line) - 1] = '\0';
	new = malloc(sizeof(t_list));
		ft_bzero(aux, BUFFERSIZE - 1);
	while (ft_isspace(line[i]))
		i++;
	ft_parse_quote(comm, line + i);
	while (ft_isascii(line[i]))      //TODO: ft_strcpy al libft
	{
		aux[j] = line[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	//printf("%s\n", aux);
	comm->splitshell = ft_splitshell(split, aux, ';');
	int h = 0;
	while (comm->splitshell[h])
	{
		printf("%s\n", comm->splitshell[h]);
		h++;
	}
	/*if (ft_strncmp(aux, "echo", 4) == 0)
	{
		//printf("1123\n");
		printf("%s\n", line + i);
		return (ft_echo(comm, line + i));
	}*/
	return (0);
}
