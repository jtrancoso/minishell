/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 20:23:03 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_parser(t_split *split)
{
	split->u = 0;
	split->v = 0;
	split->w = 0;
}

int	syntax_check(t_comm *comm, t_split *split, char *line)
{
	while (ft_isspace(line[split->u]))
		split->u++;
	if (parser_error(comm, split, line) != 0)
	{
		free(line);
		return (1);
	}
	if (ft_parse_quote(split, line + split->u))
	{
		free(line);
		return (1);
	}
	if (ft_parse_bar(split, line + split->u))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	ft_parseline(t_comm *comm, t_split *split, char *line)
{
	t_list	*list;
	char	**aux;

	list = NULL;
	init_parser(split);
	ft_init(comm);
	line = ft_strtrim(comm->final_line, "\n");
	if (syntax_check(comm, split, line))
		return (1);
	aux = ft_splitshell(split, line + split->u, ';');
	split->u = 0;
	while (aux[split->u])
		split->u++;
	ft_splitsemi(comm, split, aux);
	ft_splitpipe(list, comm, split);
	ft_splitgtgt(list, comm, split);
	ft_splitgt(list, comm, split);
	ft_splitlt(list, comm, split);
	check_dollar(list, comm, split);
	free(line);
	return (0);
}
