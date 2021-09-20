/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/20 18:09:18 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_quote(t_comm *comm, t_split *split, char *line)
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
		return (ft_error(split, 1));
	return (1);
}

int	ft_parseline(t_comm *comm, t_split *split, char *line)
{
	int		i;
	char	aux[BUFFERSIZE];
	int		j;
	t_list *list;
	t_list *new;
	t_comm *otro;
	char **splitsemi;
	char **splitpipe;
	char **splitgtgt;
	char **splitgt;
	char **splitlt;

	i = 0;
	j = 0;
	line[ft_strlen(line) - 1] = '\0';
	ft_bzero(aux, BUFFERSIZE - 1);
	while (ft_isspace(line[i]))
		i++;
	if (!ft_parse_quote(comm, split, line + i))
		return (0);
	if (parser_error(comm, split, line, "syntax") != 0)
		return(0);
	while (ft_isascii(line[i]))
	{
		aux[j] = line[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	i = 0;
	j = 0;
	splitsemi = ft_splitshell(split, aux, ';');
	while (splitsemi[i])
		i++;
	int h = 0;
	while (j < i * 2 - 1)
	{
		new = malloc(sizeof(t_list));
		otro = malloc(sizeof(t_comm));
		new->content = otro;
		ft_init(otro);
		if (j == 0 || j % 2 == 0)
		{
			((t_comm*)new->content)->t_word = ft_strdup(splitsemi[h]);
			h++;
		}
		if (j % 2 != 0)
			((t_comm*)new->content)->t_semi = 1;
		ft_lstadd_back(&comm->parse_head, new);
		j++;
	}
	ft_malloc_free(comm, splitsemi);
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			splitpipe = ft_splitshell(split, ((t_comm*)list->content)->t_word, '|');
			while (splitpipe[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm*)list->content)->t_word);
						((t_comm*)list->content)->t_word = NULL;
						((t_comm*)list->content)->t_word = ft_strdup(splitpipe[h]);
						h++;
					}
					else
					{
						new = malloc(sizeof(t_list));
						otro = malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitpipe[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm*)new->content)->t_pipe = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					j++;
				}
			}
			else
			{
				free(splitpipe[0]);
				splitpipe[0] = NULL;
			}
			ft_malloc_free(comm, splitpipe);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			splitgtgt = ft_splitshellgt(split, ((t_comm*)list->content)->t_word, '>');
			while (splitgtgt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm*)list->content)->t_word);
						((t_comm*)list->content)->t_word = NULL;
						((t_comm*)list->content)->t_word = ft_strdup(splitgtgt[h]);
						h++;
					}
					else
					{
						new = malloc(sizeof(t_list));
						otro = malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitgtgt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm*)new->content)->t_gtgt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					j++;
				}
			}
			else
			{
				free(splitgtgt[0]);
				splitgtgt[0] = NULL;
			}
			ft_malloc_free(comm, splitgtgt);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			splitgt = ft_splitshell(split, ((t_comm*)list->content)->t_word, '>');
			while (splitgt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm*)list->content)->t_word);
						((t_comm*)list->content)->t_word = NULL;
						((t_comm*)list->content)->t_word = ft_strdup(splitgt[h]);
						h++;
					}
					else
					{
						new = malloc(sizeof(t_list));
						otro = malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitgt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm*)new->content)->t_gt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					j++;
				}
			}
			else
			{
				free(splitgt[0]);
				splitgt[0] = NULL;
			}
			ft_malloc_free(comm, splitgt);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			splitlt = ft_splitshell(split, ((t_comm*)list->content)->t_word, '<');
			while (splitlt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm*)list->content)->t_word);
						((t_comm*)list->content)->t_word = NULL;
						((t_comm*)list->content)->t_word = ft_strdup(splitlt[h]);
						h++;
					}
					else
					{
						new = malloc(sizeof(t_list));
						otro = malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitlt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm*)new->content)->t_lt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					j++;
				}
			}
			else
			{
				free(splitlt[0]);
				splitlt[0] = NULL;
			}
			ft_malloc_free(comm, splitlt);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	test_list(list, comm);
	while (list)
	{
		char *dollar_id;
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			if (ft_strchr(((t_comm*)list->content)->t_word, '$'))
			{
				dollar_id = ft_parsedollar(list, comm, split, ((t_comm*)list->content)->t_word);
				free(((t_comm*)list->content)->t_word);
				((t_comm*)list->content)->t_word = ft_strdup(dollar_id);
				free(dollar_id);
			}
		}
		list = list->next;
	}
	return (0);
}
