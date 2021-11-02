/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:15:19 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/02 09:06:37 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int parse_bar(t_split *split, char *line)
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
		printf("line[i]:%c i:%d\n", line[i], i);
		if (i == 0)
		{
			printf("line[i]: %c i:%d\n", line[i], i);
			if (line[i] == '\'')
			{
				printf("here1\n");
				s_quote++;
			}
			else if (line[i] == '\"')
			{
				printf("here2\n");
				d_quote++;
			}
			else if (line[i] == '\\')
			{
				printf("no entiendor\n");
				if (line[i + 1] != '\0')
					i++;
				else
					return (ft_error(split, 7));
			}
		}
		else if (i > 0)
		{
			printf("aqui\n");
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
				printf("hola\n");
				return (ft_error(split, 7));
			}
		}
		i++;
	}*/
	/*while (line[i])
	{
		//Contador de comillas simples
		if (line[i] == '\'' && s_quote == 0)
		{
			if (i == 0)
				s_quote++;
			else if (i > 0 && line [i - 1] != '\\')
				s_quote++;
			else if (i > 0 && line [i - 1] == '\\')
			bar--;
		}
		//Contador de comillas dobles
		else if (line[i] == '\"' && d_quote == 0)
		{
			d_quote++;
		}
		//Si backslash y existe siguiente carácter avanza una posición
		if (line[i] == '\\' && line[i + 1] && (s_quote % 2 == 0 || d_quote % 2 == 0))
		{
			ft_putchar_fd('-', 1);
			ft_putchar_fd(line[i], 1);
			i++;
		} 
		//Si backslash y no existen más carácteres incrementar barra
		else if ((line[i] == '\\' && !line[i + 1])) 
		// || (line[i] == '\\' && line[i + 1] != '\\')) pertenece a lo anteior
		{
			bar++;
			printf("Contador barras - %d:\n", bar);
		}
		i++;
	}*/
	/*if (bar % 2 != 0)
		return (ft_error(split, 7));
	else
		return (1);
}*/

void ft_echo(t_list *list, t_comm *comm, t_split *split)
{
	int i;
	int j;
	int q;

	i = 1;
	q = 1;
	comm->flag_n = 0;
	printf("llego con estas cadenas:");
	while (comm->cmd.cmd[q])
	{
		printf("llego con estas cadenas:%s", comm->cmd.cmd[q]);
		q++;
	}
	printf("\n");
	q = 1;
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
		//if (parse_bar(split, comm->cmd.cmd[i]) == -1)
		//	return ;
		//printf("Hola\n");
		while (comm->cmd.cmd[i][j])
		{
			//if (comm->cmd.cmd[i][j] == '\\' && comm->cmd.cmd[i][j + 1])
			//	j++;
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