/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:15:03 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/28 13:52:51 by jtrancos         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>

typedef struct	s_env
{
	char *id;
	char *value; 
}				t_env;

typedef struct s_echo
{
	int	flag_n;
}				t_echo;

typedef struct s_cmd
{
	char **cmd;
	char *path;
	char **env_array;
}				t_cmd;


typedef	struct	s_split //FIXME: meterlo en t_comm
{
	int f_simple;
	int f_double;
	int errorcode;
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
	int		freed;
	int		pid;
	char	*user;

	t_echo	echo;
	t_list	*env_head;
	t_list	*parse_head;
	t_cmd	cmd;
}				t_comm;

int				ft_parseline(t_comm *comm, t_split *split, char *line);
int				ft_echo(t_comm *comm, char *line);
void			ft_init(t_comm *comm);
int				ft_error(t_split *split, int error);
char			**ft_splitshell(t_split *split, char const *s, char c);
char			**ft_splitshellgt(t_split *split, char const *s, char c);
char			*ft_parsedollar(t_list *list, t_comm *comm, t_split *split, char *line);
void			check_quote(t_split *split, const char *c);
void 			test_list(t_list *list, t_comm *comm);
void 			clear_list(t_list *list, t_comm *comm);
void 			free_list(void *cont);
void			free_env(void *cont);
int				parse_command(t_list *list, t_comm *comm, t_split *split);
void			ft_malloc_free(t_comm *comm, char **str, int i);
int				parser_error (t_comm *comm, t_split *split, char *line, char *mode);
void			ft_exit(t_list *list, t_comm *comm);
void			ft_pwd(t_list *list, t_comm *comm);
void			ft_cd(t_list *list, t_comm *comm, t_split *split);
void			ft_env(t_list *list, t_comm *comm, t_split *split);
void			ft_export(t_list *list, t_comm *comm, t_split *split);
char			**ft_superglue(t_list *list, t_comm *comm);



#endif