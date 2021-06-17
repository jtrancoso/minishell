/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:46:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/06/17 14:58:01 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_inverted_var(const char *c)
{
	//printf("2--      c: %c\n",c[0]);
	if ((int)c[0] == '\\' && (int)c[0] != '\0' && ((int)c[1] == '$'))
		return (1);
	return (0);
}

char	*ft_parsedollar(t_list *list, t_comm *comm, t_split *split, char *line)
{
	char *aux;
	char *aux_id;
	int	lmax;
	
	list = comm->env_head;
	lmax = 0;
	int i = 0;
	int j = 0;
	int q = 0;
	while (line[i])
	{
		if (line[i] == '$')
			j++;
		i++;
	}
	printf("%d\n", j);
	while (list)
	{
		//printf("id: %s\nvalue: %s \n", (((t_env*)list->content)->id),(((t_env*)list->content)->value));
		if (ft_strlen(((t_env*)list->content)->value) > lmax)
			lmax = ft_strlen(((t_env*)list->content)->value);
		list = list->next;
	}
	aux = malloc(sizeof(char *) * (lmax * j) + 1);
	aux_id = malloc(sizeof(char *) * (ft_strlen(line)));
	i = 0;
	j = 0;
	split->f_simple = 0;
	split->f_double = 0;
	while (line[i])
	{
		printf("c: %c\n", line[i]);
		if (check_inverted_var(&line[i]) == 1)
			i += 2;
		check_quote(split, &line[i]);
		if (line[i] != '$' || (line[i] == '$' && split->f_simple != 0) || (line[i] == '$' && line[i - 1] == '\\' && i != 0))
		{
			aux[j] = line[i];
			j++;
		}
		else if (line[i] == '$')
		{
			i++;
			printf("%c\n", line[i]);
			while (line[i] != ' ' && line[i] != '\0')
			{
				printf("dentro: %c\n", line[i]);
				aux_id[q] = line[i];
				q++;
				i++;
			}
			aux_id[q] = '\0';
			printf("%s\n", aux_id);
			//expand_quote(comm, aux_id);
		}
		i++;
	}
	aux[j] = '\0';
	printf("aux: %s\n", aux);
	free (aux);
	free (aux_id);
	return ("hola");

}