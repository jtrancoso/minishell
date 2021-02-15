/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:15:03 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/15 17:16:16 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFERSIZE 4096

/*
** command = echo, cd, pwd...
**	arg = hola, ../
**	flags = -n
*/

typedef struct	s_echo
{
	int			flag_n;
}				t_echo;


typedef struct	s_comm
{
	char 		*command;
	char		*arg;
	char		*flag;
	t_echo		echo;
}				t_comm;

# include "printf/libftprintf.h"
# include <stdio.h>
# include <unistd.h>

int		ft_parseline(t_comm *comm, char *line);
int		ft_isspace(int c);
int		ft_echo(t_comm *comm, char *line);
void	ft_init(t_comm *comm);


#endif