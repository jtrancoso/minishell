/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:22:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/23 13:31:03 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(t_comm *comm)
{
	comm->t_command = NULL;
	comm->t_word = NULL;
	comm->t_pipe = 0;
	comm->t_semi = 0;
	comm->t_gt = 0;
	comm->t_gtgt = 0;
	comm->t_lt = 0;
	comm->freed = 0;
}

void	ft_malloc_free(t_comm *comm, char **str, int i)
{
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str[i]);
	free (str);
}

void free_list(void *cont)
{
	if (((t_comm *)cont)->t_word)
		free(((t_comm *)cont)->t_word);
	free((t_comm *)cont);
}

void free_env(void *cont)
{
	if (((t_env *)cont)->id)
		free(((t_env *)cont)->id);
	if (((t_env *)cont)->value)
		free(((t_env *)cont)->value);
	free((t_env *)cont);
}

void check_quote(t_split *split, const char *c)
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
