/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/12 14:12:22 by jtrancos         ###   ########.fr       */
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
		if (i == 0 && line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			i += 1;
		else
		{
			if ((line[i] == '\\' && line[i + 1] == '\"') || (line[i] == '\\' && line[i + 1] == '\'' && s_quote % 2 == 0))
				i+= 1;
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
		return (ft_error(split, NULL , 1)); //TODO: me he quedado aqui
	return (0);
}

int ft_parse_bar(t_comm *comm, t_split *split, char *line)
{
	int i;
	int bar; //Contador barras
	int s_quote; //Contador comillas dobles
	int d_quote; //Contador comillas simples

	i = 0;
	bar = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i])
	{
		//printf("line[i]:%c i:%d\n", line[i], i);
		if (i == 0)
		{
			//printf("line[i]: %c i:%d\n", line[i], i);
			if (line[i] == '\'')
			{
				//printf("here1\n");
				s_quote++;
			}
			else if (line[i] == '\"')
			{
				//printf("here2\n");
				d_quote++;
			}
			else if (line[i] == '\\')
			{
				//printf("no entiendor\n");
				if (line[i + 1] != '\0')
					i++;
				else
					return (ft_error(split, NULL, 7));
			}
		}
		else if (i > 0)
		{
			//printf("aqui\n");
			if (d_quote % 2 != 0 && line[i] == '\"' && line[i - 1] != '\\')
				d_quote++;
			else if (d_quote % 2 != 0 && line[i] == '\"' && line[i - 1] == '\\')
				i++;
			else if (s_quote % 2 != 0)
				s_quote++;
			else if (line[i] == '\\' && line[i + 1])
				i++;
			else if (line[i] == '\\' && line[i + 1] == '\0')
			{
				//printf("hola\n");
				return (ft_error(split, NULL, 7));
			}
		}
		i++;
	}
	if (bar % 2 != 0)
		return (ft_error(split, NULL, 7));
	else
		return (0);
}

int	ft_parseline(t_comm *comm, t_split *split, char *line)
{
	int		i;
	int		j;
	int		h;
	t_list *list;
	t_list *new;
	t_comm *otro;
	char **splitsemi;
	char **splitpipe;
	char **splitgtgt;
	char **splitltlt;
	char **splitgt;
	char **splitlt;

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
	i = 0;
	j = 0;
	h = 0;
	splitsemi = ft_splitshell(split, line, ';');
	while (splitsemi[i])
		i++;
	comm->parse_head = NULL;
	while (j < i * 2 - 1)
	{
		new = ft_malloc(sizeof(t_list));
		otro = ft_malloc(sizeof(t_comm));
		new->content = otro;
		ft_init((t_comm*)new->content);   //TODO: comprobar si esto realmente funciona o podemos dejarlo como init(otro)
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
	ft_malloc_free(comm, splitsemi, 0);
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
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm*)new->content);
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
			ft_malloc_free(comm, splitpipe, 0);
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
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm*)new->content);
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
			ft_malloc_free(comm, splitgtgt, 0);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	/*while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			splitltlt = ft_splitshellgt(split, ((t_comm*)list->content)->t_word, '<');
			while (splitltlt[i])
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
						((t_comm*)list->content)->t_word = ft_strdup(splitltlt[h]);
						h++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitltlt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm*)new->content)->t_ltlt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					j++;
				}
			}
			else
			{
				free(splitltlt[0]);
				splitltlt[0] = NULL;
			}
			ft_malloc_free(comm, splitltlt, 0);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}*/
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
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm*)new->content);
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
			ft_malloc_free(comm, splitgt, 0);
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
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm*)new->content);
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
			ft_malloc_free(comm, splitlt, 0);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	//test_list(list, comm);
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
	free(line);
	return (0);
}
