/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:15:03 by jtrancos          #+#    #+#             */
/*   Updated: 2021/05/13 13:16:17 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFERSIZE 4096

/*
	command = echo, cd, pwd...
	arg = hola, ../
	flags = -n
*/

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>


typedef struct s_echo
{
	int	flag_n;
}				t_echo;

typedef	struct	s_split
{
	int f_simple;
	int f_double;
}				t_split;

typedef struct s_comm
{
	char	*t_command;
	char	*t_word;
	int		t_pipe;
	int		t_semi;
	int		t_gt;
	int		t_gtgt;
	int		t_lt;
	char	**splitshell;
	char	**splitpipe;
	t_echo	echo;
}				t_comm;

int		ft_parseline(t_comm *comm, t_split *split, char *line);
int		ft_echo(t_comm *comm, char *line);
void	ft_init(t_comm *comm);
int		ft_error(int error);
char	**ft_splitshell(t_split *split, char const *s, char c);

#endif