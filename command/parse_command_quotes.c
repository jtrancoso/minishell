/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:30:22 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/15 13:09:43 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	even_quotes_and_bar(t_comm *comm, t_split *split, char **aux)
{
	split->k++;
	if (comm->cmd.cmd[split->i][split->k] == '\\'
		|| comm->cmd.cmd[split->i][split->k] == '\''
		|| comm->cmd.cmd[split->i][split->k] == '\"'
		|| comm->cmd.cmd[split->i][split->k] == '~')
	{
		aux[split->j][split->l++] = comm->cmd.cmd[split->i][split->k];
		if (comm->cmd.cmd[split->i][split->k + 1] == '~')
			comm->f_verg = 1;
	}
}

void	even_quotes(t_comm *comm, t_split *split, char **aux)
{
	if (comm->cmd.cmd[split->i][split->k] == '\\')
		even_quotes_and_bar(comm, split, aux);
	else if (comm->cmd.cmd[split->i][split->k] == '\'')
	{
		split->s_quote++;
		if (comm->cmd.cmd[split->i][split->k + 1] == '~')
			comm->f_verg = 1;
	}
	else if (comm->cmd.cmd[split->i][split->k] == '\"')
	{
		split->d_quote++;
		if (comm->cmd.cmd[split->i][split->k + 1] == '~')
			comm->f_verg = 1;
	}
	else
		aux[split->j][split->l++] = comm->cmd.cmd[split->i][split->k];
}

void	uneven_dquote(t_comm *comm, t_split *split, char **aux)
{
	if (comm->cmd.cmd[split->i][split->k] == '\\')
	{
		split->k++;
		if (comm->cmd.cmd[split->i][split->k] == '\''
			|| (comm->cmd.cmd[split->i][split->k] != '\\'
			&& comm->cmd.cmd[split->i][split->k] != '\"'))
		{
			aux[split->j][split->l++] = '\\';
			aux[split->j][split->l++] = comm->cmd.cmd[split->i][split->k];
		}
		else if (comm->cmd.cmd[split->i][split->k] == '\\'
			|| comm->cmd.cmd[split->i][split->k] == '\"')
			aux[split->j][split->l++] = comm->cmd.cmd[split->i][split->k];
	}
	else if (comm->cmd.cmd[split->i][split->k] == '\"')
		split->d_quote++;
	else
		aux[split->j][split->l++] = comm->cmd.cmd[split->i][split->k];
}

void	quote_loop(t_comm *comm, t_split *split, char **aux)
{
	if (split->s_quote % 2 == 0 && split->d_quote % 2 == 0)
		even_quotes(comm, split, aux);
	else if (split->s_quote % 2 != 0)
	{
		if (comm->cmd.cmd[split->i][split->k] == '\'')
			split->s_quote++;
		else
			aux[split->j][split->l++] = comm->cmd.cmd[split->i][split->k];
	}
	else if (split->d_quote % 2 != 0)
		uneven_dquote(comm, split, aux);
	split->k++;
}

void	clean_quotes(t_list *list, t_comm *comm, t_split *split)
{
	char	**aux;

	init_var_clean_quotes(list, comm, split);
	while (comm->cmd.cmd[split->i])
		split->i++;
	aux = ft_malloc(sizeof(char **) * (split->i + 1));
	split->i = 0;
	while (comm->cmd.cmd[split->i])
	{
		split->l = 0;
		split->k = 0;
		aux[split->j] = ft_malloc(sizeof(char *)
				* (ft_strlen(comm->cmd.cmd[split->i])) + 1);
		while (comm->cmd.cmd[split->i][split->k])
			quote_loop(comm, split, aux);
		aux[split->j][split->l] = '\0';
		split->i++;
		split->j++;
	}
	aux[split->j] = NULL;
	fill_str(list, comm, split, aux);
	ft_malloc_free(comm, aux, split->j);
}
