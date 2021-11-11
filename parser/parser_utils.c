/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:22:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/11 12:22:54 by jtrancos         ###   ########.fr       */
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
	comm->t_ltlt = 0;
	comm->freed = 0;
	comm->f_d = 0;
	comm->f_s = 0;
	comm->fd = 1;
	comm->page = 1;
	comm->export.ret = 0;
	comm->export.f_valid = 0; //la podemos si hace falta
	comm->export.f_exist = 0;
	comm->prev_pipe = 0;
	comm->post_pipe = 0;
	comm->redir.file = NULL;
	comm->redir.rest = NULL;
	comm->redir.last_fdin = 1;
	comm->redir.last_fdout = 1;
	comm->redir.t_append = 0;
	comm->redir.t_create = 0;
	comm->redir.t_trunc = 0;
	comm->dir = NULL;
	comm->home = NULL;
	comm->f_verg = 0;
}

void	ft_malloc_free(t_comm *comm, char **str, int i)
{
	/*int j = 0;
	while (str[j])
	{
		printf("paths: %s\n", str[j]);
		j++;
	}
	printf("i: %d\n", i);*/
	while (str[i])
	{
		//printf("str: %s\n", str[i]);
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void	free_list(void *cont)
{
	if (((t_comm *)cont)->t_word)
		free(((t_comm *)cont)->t_word);
	if (((t_comm *)cont)->t_command)
		free(((t_comm *)cont)->t_command);
	if (((t_comm *)cont)->redir.file)
		free(((t_comm *)cont)->redir.file);
	if (((t_comm *)cont)->redir.rest)
		free(((t_comm *)cont)->redir.rest);
	free((t_comm *)cont);
}

void	free_env(void *cont)
{
	if (((t_env *)cont)->id)
		free(((t_env *)cont)->id);
	if (((t_env *)cont)->value)
		free(((t_env *)cont)->value);
	free((t_env *)cont);
}

void	free_export(void *cont)
{
	if (((t_export *)cont)->id)
		free(((t_export *)cont)->id);
	if (((t_export *)cont)->value)
		free(((t_export *)cont)->value);
	free((t_export *)cont);
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
