/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:30:22 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/14 11:42:55 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var_clean_quotes(t_list *list, t_comm *comm, t_split *split)
{
	split->s_quote = 0;
	split->d_quote = 0;
	split->k = 0;
	split->str = NULL;
}

void	fill_str(t_list *list, t_comm *comm, t_split *split, char **aux)
{
	int	i;

	i = 0;
	while (aux[i])
	{
		split->str = ft_strdup(comm->cmd.cmd[i]);
		free(comm->cmd.cmd[i]);
		comm->cmd.cmd[i] = aux[i];
		free(split->str);
		i++;
	}
}

void	clean_quotes(t_list *list, t_comm *comm, t_split *split)
{
	char	**aux;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	init_var_clean_quotes(list, comm, split);
	while (comm->cmd.cmd[i])
		i++;
	aux = ft_malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (comm->cmd.cmd[i])
	{
		l = 0;
		printf("--l1: %d\n", l);
		split->k = 0;
		aux[j] = ft_malloc(sizeof(char *) * (ft_strlen(comm->cmd.cmd[i])) + 1);
		while (comm->cmd.cmd[i][split->k])
		{
			printf("--l3: %d\n", l);
			if (split->s_quote % 2 == 0 && split->d_quote % 2 == 0)
			{
				if (comm->cmd.cmd[i][split->k] == '\\')
				{
					split->k++;
					if (comm->cmd.cmd[i][split->k] == '\\' || comm->cmd.cmd[i][split->k] == '\'' || comm->cmd.cmd[i][split->k] == '\"' || comm->cmd.cmd[i][split->k] == '~')
					{
						aux[j][l++] = comm->cmd.cmd[i][split->k];
						if (comm->cmd.cmd[i][split->k + 1] == '~')
							comm->f_verg = 1;
					}
				}
				else if (comm->cmd.cmd[i][split->k] == '\'')
				{
					split->s_quote++;
					if (comm->cmd.cmd[i][split->k + 1] == '~')
						comm->f_verg = 1;
				}
				else if (comm->cmd.cmd[i][split->k] == '\"')
				{
					split->d_quote++;
					if (comm->cmd.cmd[i][split->k + 1] == '~')
						comm->f_verg = 1;
				}
				else
					aux[j][l++] = comm->cmd.cmd[i][split->k];
			}
			else if (split->s_quote % 2 != 0)
			{
				if (comm->cmd.cmd[i][split->k] == '\'')
					split->s_quote++;
				else
					aux[j][l++] = comm->cmd.cmd[i][split->k];
			}
			else if (split->d_quote % 2 != 0)
			{
				if (comm->cmd.cmd[i][split->k] == '\\')
				{
					split->k++;
					if (comm->cmd.cmd[i][split->k] == '\'' || (comm->cmd.cmd[i][split->k] != '\\' && comm->cmd.cmd[i][split->k] != '\"'))
					{
						aux[j][l++] = '\\';
						aux[j][l++] = comm->cmd.cmd[i][split->k];
					}
					else if (comm->cmd.cmd[i][split->k] == '\\' || comm->cmd.cmd[i][split->k] == '\"')
						aux[j][l++] = comm->cmd.cmd[i][split->k];
				}
				else if (comm->cmd.cmd[i][split->k] == '\"')
					split->d_quote++;
				else
					aux[j][l++] = comm->cmd.cmd[i][split->k];
			}
			split->k++;
		}
		aux[j][l] = '\0';
		i++;
		j++;
		printf("--l2: %d\n", l);
	}
	aux[j] = NULL;
    fill_str(list, comm, split, aux);
	ft_malloc_free(comm, aux, j);
}
