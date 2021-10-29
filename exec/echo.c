/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:15:19 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/29 14:22:55 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parse_bar(t_split *split, char *line)
{
	int i;
	int bar;
	i = 0;
	bar = 0;
	int s_quote;
	int d_quote;

	s_quote = 0;
	d_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && s_quote == 0)  /*Contador de comillas simples*/
		{
			if (i = 0)
				s_quote++;
			else if (i > 0 && line [i - 1] != '\\')
				s_quote++;
			else if (i > 0 && line [i - 1] == '\\')
			bar--;
		}
		else if (line[i] == '\"' && d_quote == 0) /*Contador de comillas dobles*/
		{
			d_quote++;
		}
		if (line[i] == '\\' && line[i + 1] && (s_quote % 2 == 0 || d_quote % 2 == 0)) /*Si backslash y existe siguiente carácter avanza una posició*/
		{
			ft_putchar_fd('-', 1);
			ft_putchar_fd(line[i], 1);
			i++;
		} /*Si backslash y no existen más carácteres incrementar barra*/
		else if ((line[i] == '\\' && !line[i + 1]))/* || (line[i] == '\\' && line[i + 1] != '\\'))*/
		{
			bar++;
			printf("Contador barras - %d:\n", bar);
		}
		i++;
	}
	if (bar % 2 != 0)
		return (ft_error(split, 7));
	else
		return (1);
}
void ft_echo(t_list *list, t_comm *comm, t_split *split)
{
	int i;
	int j;
	int q;

	i = 1;
	q = 1;
	comm->flag_n = 0;
	while (comm->cmd.cmd[q])
		q++;
	while (i < q && (ft_strncmp(comm->cmd.cmd[i], "-n", 2) == 0))
	{
		comm->flag_n = 1;
		i++;
	}
	while (comm->cmd.cmd[i])
	{
		j = 0;
		if (parse_bar(split, comm->cmd.cmd[i]) == -1)
			return ;
		printf("Hola\n");
		while (comm->cmd.cmd[i][j])
		{
			if (comm->cmd.cmd[i][j] == '\\' && comm->cmd.cmd[i][j + 1])
				j++;
			ft_putchar_fd(comm->cmd.cmd[i][j], 1);
			j++;
		}
		if (comm->cmd.cmd[i + 1])
			ft_putchar_fd(' ',  1);
		i++;
	}
	if (!comm->flag_n)
		ft_putchar_fd('\n', 1);
}