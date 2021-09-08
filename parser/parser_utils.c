/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:22:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/08 12:20:20 by jtrancos         ###   ########.fr       */
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

void free_list(void *cont)
{
	if (((t_comm *)cont)->t_word)
		free(((t_comm *)cont)->t_word);
	free((t_comm *)cont);
}

void check_quote(t_split *split, const char *c)
{
	//printf("%s\n", c);
	if ((int)c[0] == '\"' && split->f_double == 0 && split->f_simple == 0)
		split->f_double = 1;
	else if ((int)c[0] == '\'' && split->f_double == 0 && split->f_simple == 0)
		split->f_simple = 1;
	else if ((int)c[0] == '\"' && split->f_double == 1 && split->f_simple == 0)
		split->f_double = 0;
	else if ((int)c[0] == '\'' && split->f_double == 0 && split->f_simple == 1)
		split->f_simple = 0;
	//printf("%c-%i", c[0], (int)c[0]);
	//printf("flag: d%d\n", split->f_double);
	//printf("letra: %c flag_s: %d flag_d: %d\n", c[0],  split->f_simple, split->f_double);   
}
