/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 14:25:35 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void ft_splitpipe(t_list	*list, t_comm *comm, t_split *split, char *line)
{
	char	**aux;
	t_list	*new;
	t_comm	*otro;
		
	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '|');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
			{
				while (split->v < split->u * 2 - 1 && list)
				{
					if (split->v == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(aux[split->w]);
						split->w++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (split->v % 2 == 0 && split->v != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(aux[split->w]);
							split->w++;
						}
						else if (split->v % 2 != 0)
							((t_comm *)new->content)->t_pipe = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					split->v++;
				}
			}
			else
			{
				free(aux[0]);
				aux[0] = NULL;
			}
			ft_malloc_free(comm, aux, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}	
}*/

void	init_parser(t_split *split)
{
	split->u = 0;
	split->v = 0;
	split->w = 0;
}

int	ft_parseline(t_comm *comm, t_split *split, char *line)
{
	t_list	*list;
	t_list	*new;
	t_comm	*otro;
	char	**aux;

	init_parser(split);
	ft_init(comm); //TODO: no se si esto afecta en algo
	line = ft_strtrim(comm->final_line, "\n");
	while (ft_isspace(line[split->u]))
		split->u++;
	if (ft_parse_quote(comm, split, line + split->u))
	{
		free(line);
		return (1);
	}
	if (ft_parse_bar(comm, split, line + split->u))
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
	aux = ft_splitshell(split, line + split->u, ';');
	split->u = 0;
	while (aux[split->u])
		split->u++;
	comm->parse_head = NULL;
	while (split->v < split->u * 2 - 1)
	{
		new = ft_malloc(sizeof(t_list));
		otro = ft_malloc(sizeof(t_comm));
		new->content = otro;
		ft_init((t_comm *)new->content);//TODO: comprobar si esto realmente funciona o podemos dejarlo como init(otro)
		if (split->v == 0 || split->v % 2 == 0)
		{
			((t_comm *)new->content)->t_word = ft_strdup(aux[split->w]);
			split->w++;
		}
		if (split->v % 2 != 0)
			((t_comm *)new->content)->t_semi = 1;
		ft_lstadd_back(&comm->parse_head, new);
		split->v++;
	}
	ft_malloc_free(comm, aux, 0);
	ft_splitpipe(list, comm, split, line);
	/*list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '|');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
			{
				while (split->v < split->u * 2 - 1 && list)
				{
					if (split->v == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(aux[split->w]);
						split->w++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (split->v % 2 == 0 && split->v != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(aux[split->w]);
							split->w++;
						}
						else if (split->v % 2 != 0)
							((t_comm *)new->content)->t_pipe = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					split->v++;
				}
			}
			else
			{
				free(aux[0]);
				aux[0] = NULL;
			}
			ft_malloc_free(comm, aux, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}*/
	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshellgt(split,
					((t_comm *)list->content)->t_word, '>');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
			{
				while (split->v < split->u * 2 - 1 && list)
				{
					if (split->v == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(aux[split->w]);
						split->w++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (split->v % 2 == 0 && split->v != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(aux[split->w]);
							split->w++;
						}
						else if (split->v % 2 != 0)
							((t_comm *)new->content)->t_gtgt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					split->v++;
				}
			}
			else
			{
				free(aux[0]);
				aux[0] = NULL;
			}
			ft_malloc_free(comm, aux, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '>');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
			{
				while (split->v < split->u * 2 - 1 && list)
				{
					if (split->v == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(aux[split->w]);
						split->w++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (split->v % 2 == 0 && split->v != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(aux[split->w]);
							split->w++;
						}
						else if (split->v % 2 != 0)
							((t_comm *)new->content)->t_gt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					split->v++;
				}
			}
			else
			{
				free(aux[0]);
				aux[0] = NULL;
			}
			ft_malloc_free(comm, aux, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '<');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
			{
				while (split->v < split->u * 2 - 1 && list)
				{
					if (split->v == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(aux[split->w]);
						split->w++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (split->v % 2 == 0 && split->v != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(aux[split->w]);
							split->w++;
						}
						else if (split->v % 2 != 0)
							((t_comm *)new->content)->t_lt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					split->v++;
				}
			}
			else
			{
				free(aux[0]);
				aux[0] = NULL;
			}
			ft_malloc_free(comm, aux, 0);
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
		split->u = 0;
		split->v = 0;
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
