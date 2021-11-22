/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 10:06:27 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_quote(t_comm *comm, t_split *split, char *line)
{
	int	s_quote;
	int	d_quote;
	int	i;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	/*while (line[i])
	{
		if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			i += 2;
		if (line[i] == '\"' && s_quote % 2 == 0)
			d_quote++;
		if (line[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		i++;
	}*/
	while (line[i])
	{
		if (i == 0 && line[i] == '\\' && (line[i + 1] == '\"'
				|| line[i + 1] == '\''))
			i += 1;
		else
		{
			if ((line[i] == '\\' && line[i + 1] == '\"') || (line[i] == '\\'
					&& line[i + 1] == '\'' && s_quote % 2 == 0))
				i += 1;
			else if (line[i] == '\\' && line[i + 1] == '\'' && s_quote % 2 != 0)
			{
				i++;
				s_quote++;
			}
			else if (line[i] == '\"' && s_quote % 2 == 0)
				d_quote++;
			else if (line[i] == '\'' && d_quote % 2 == 0)
				s_quote++;
		}
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		return (ft_error(split, NULL, 1));
	return (0);
}

int	ft_parseline(t_comm *comm, t_split *split, char *line)
{
	int		i;
	int		j;
	int		h;
	t_list	*list;
	t_list	*new;
	t_comm	*otro;
	char	**splitsemi;
	char	**splitpipe;
	char	**splitgtgt;
	char	**splitltlt;
	char	**splitgt;
	char	**splitlt;

	i = 0;
	ft_init(comm); //TODO: no se si esto afecta en algo
	line = ft_strtrim(comm->final_line, "\n");
	while (ft_isspace(line[i]))
		i++;
	if (ft_parse_quote(comm, split, line + i))
	{
		free(line);
		return (1);
	}
	if (ft_parse_bar(comm, split, line + i))
	{
		free(line);
		return (1);
	}
	//test_list(list, comm);
	if (parser_error(comm, split, line) != 0)
	{
		free(line);
		return (1);
	}
	j = 0;
	h = 0;
	splitsemi = ft_splitshell(split, line + i, ';');
	i = 0;
	while (splitsemi[i])
		i++;
	comm->parse_head = NULL;
	while (j < i * 2 - 1)
	{
		new = ft_malloc(sizeof(t_list));
		otro = ft_malloc(sizeof(t_comm));
		new->content = otro;
		ft_init((t_comm *)new->content);//TODO: comprobar si esto realmente funciona o podemos dejarlo como init(otro)
		if (j == 0 || j % 2 == 0)
		{
			((t_comm *)new->content)->t_word = ft_strdup(splitsemi[h]);
			h++;
		}
		if (j % 2 != 0)
			((t_comm *)new->content)->t_semi = 1;
		ft_lstadd_back(&comm->parse_head, new);
		j++;
	}
	ft_malloc_free(comm, splitsemi, 0);
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm *)list->content)->t_word)
		{
			splitpipe = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '|');
			while (splitpipe[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(splitpipe[h]);
						h++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(splitpipe[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm *)new->content)->t_pipe = 1;
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
			ft_malloc_free(comm, splitpipe, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm *)list->content)->t_word)
		{
			splitgtgt = ft_splitshellgt(split,
					((t_comm *)list->content)->t_word, '>');
			while (splitgtgt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(splitgtgt[h]);
						h++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(splitgtgt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm *)new->content)->t_gtgt = 1;
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
			ft_malloc_free(comm, splitgtgt, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm *)list->content)->t_word)
		{
			splitgt = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '>');
			while (splitgt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(splitgt[h]);
						h++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(splitgt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm *)new->content)->t_gt = 1;
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
			ft_malloc_free(comm, splitgt, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm *)list->content)->t_word)
		{
			splitlt = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '<');
			while (splitlt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(splitlt[h]);
						h++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(splitlt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm *)new->content)->t_lt = 1;
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
			ft_malloc_free(comm, splitlt, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	//test_list(list, comm);
	while (list)
	{
		char	*dollar_id;
		i = 0;
		j = 0;
		if (((t_comm *)list->content)->t_word)
		{
			if (ft_strchr(((t_comm *)list->content)->t_word, '$'))
			{
				dollar_id = ft_parsedollar(list, comm, split,
						((t_comm *)list->content)->t_word);
				free(((t_comm *)list->content)->t_word);
				((t_comm *)list->content)->t_word = ft_strdup(dollar_id);
				free(dollar_id);
			}
		}
		list = list->next;
	}
	free(line);
	return (0);
}
