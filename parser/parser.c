/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/05/21 14:25:31 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: sacar los splits del comm y jugar con la estructura

void	ft_malloc_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		printf("%s\n", str[i]);
		free(str[i]);
		i++;
	}
	free(str);
}


int	ft_parse_quote(t_comm *comm, char *line)
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
		return (ft_error(1));
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
	int freed = 0;
	
	i = 0;
	j = 0;
	line[ft_strlen(line) - 1] = '\0';
	ft_bzero(aux, BUFFERSIZE - 1);
	while (ft_isspace(line[i]))
		i++;
	if (!ft_parse_quote(comm, line + i))
		return (0);
	while (ft_isascii(line[i]))      //TODO: ft_strcpy al libft
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
	ft_malloc_free(splitsemi);
	list = comm->parse_head;
	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			printf("original word: %s\n", ((t_comm*)list->content)->t_word);
			splitpipe = ft_splitshell(split, ((t_comm*)list->content)->t_word, '|');
			//printf("original pipe: %s\n", splitpipe[i + 1]);
			while (splitpipe[i])
			{
				printf("pipe[%d]: %s\n", i, splitpipe[i]);
				i++;
			}
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
						//free(splitpipe[h]);
						h++;
					}
					else
					{
						new = malloc(sizeof(t_list));   //TODO: mirar ahorrar lineas list_new 
						otro = malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitpipe[h]);
							//free(splitpipe[h]);
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
				printf("freepipe: %s\n", splitpipe[0]);
				free(splitpipe[0]);
				freed = 1;
				splitpipe[0] = NULL;
			}
		}
		else
		{
			printf("wordperdido: %s\n", ((t_comm*)list->content)->t_word);
			free(((t_comm*)list->content)->t_word);
		}
		//printf("word: %s pipe: %d semi: %d\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi);
		list = list->next;
	}
	if (freed == 1)
		free(splitpipe);
	else
		ft_malloc_free(splitpipe);
	list = comm->parse_head;
	/*while (list)
	{
		printf("word: %s pipe: %d semi: %d\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi);
		list = list->next;
	}*/
	//printf("7\n");


	/*h = 0;
	while (comm->splitshell[h])
	{
		printf("splitshell%d %s\n", h, comm->splitshell[h]);
		h++;
	}
	h = 0;
	while (comm->splitpipe[h])
	{
		printf("splitpipe%d %s\n", h, comm->splitpipe[h]);
		h++;
	}*/
	/*if (ft_strncmp(aux, "echo", 4) == 0)
	{
		//printf("1123\n");
		printf("%s\n", line + i);
		return (ft_echo(comm, line + i));
	}*/
	return (0);
}
