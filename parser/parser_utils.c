/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:22:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/16 09:59:16 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: hacer el ft_malloc protegido

void	*ft_malloc(size_t size)
{
	char	*aux;

	aux = malloc(size);
	if (!aux)
	{
		printf("malloc error\n");
		exit (1);
	}
	return (aux);
}

void	ft_malloc_free(t_comm *comm, char **str, int i)
{
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void	check_quote(t_split *split, const char *c)
{
	if ((int)c[0] == '\"' && split->f_double == 0 && split->f_simple == 0)
		split->f_double = 1;
	else if ((int)c[0] == '\'' && split->f_double == 0 && split->f_simple == 0)
		split->f_simple = 1;
	else if ((int)c[0] == '\"' && split->f_double == 1 && split->f_simple == 0)
		split->f_double = 0;
	else if ((int)c[0] == '\'' && split->f_double == 0 && split->f_simple == 1)
		split->f_simple = 0;
}

int	check_inverted_var(const char *c)
{
	if ((int)c[0] == '\\' && (int)c[0] != '\0' && ((int)c[1] == '$'))
		return (1);
	return (0);
}
