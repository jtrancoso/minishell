/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:15:03 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/11 19:59:08 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFERSIZE 4096
# define ART "\
             _            _   _             _          _ _  \n\
  __ _  __ _| | __ _  ___| |_(_) ___    ___| |__   ___| | | \n\
 / _` |/ _` | |/ _` |/ __| __| |/ __|  / __| '_ \\ / _ \\ | | \n\
| (_| | (_| | | (_| | (__| |_| | (__   \\__ \\ | | |  __/ | | \n\
 \\__, |\\__,_|_|\\__,_|\\___|\\__|_|\\___|  |___/_| |_|\\___|_|_| \n\
  |___/                                                      \n\n"

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <locale.h>
# include <signal.h>

typedef struct s_env
{
	char	*id;
	char	*value;
}				t_env;

typedef struct s_path
{
	int			is_stat;
}				t_path;

typedef struct s_line
{
	int		bit_read;
	char	char_read[2];
	int		i;
	char	*tmp;
	char	*join_line;
}				t_line;

typedef struct s_export
{
	int		f_valid;
	int		f_exist;
	int		ret;
	char	*id;
	char	*value;
}				t_export;

typedef struct s_redir
{
	int		last_fdin;
	int		last_fdout;
	char	*file;
	char	*rest;
	int		t_create;
	int		t_append;
	int		t_trunc;
}				t_redir;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	**env_array;
}				t_cmd;

typedef	struct s_split //FIXME: meterlo en t_comm
{
	int	f_simple;
	int	f_double;
	int	errorcode;
	int	ret;
}				t_split;

typedef struct s_comm
{
	char		*t_command; //TODO: comprobar uso y borrar si hace falta
	char		*t_word;
	char		*final_line;
	int			t_pipe;
	int			t_semi;
	int			t_gt;
	int			t_gtgt;
	int			t_lt;
	int			freed;
	int			pid;
	int			prev_pipe;
	int			post_pipe;
	char		*user;
	char		*dir;
	char		*home;
	int			f_verg; // flag para la vergulilla
	int			f_d;
	int			f_s;
	int			flag_n;
	int			fd;
	int			page;

	t_export	export;
	t_list		*env_head;
	t_list		*parse_head;
	t_list		*export_head;
	t_cmd		cmd;
	t_redir		redir;
	t_path		path;
}				t_comm;

int				ft_parseline(t_comm *comm, t_split *split, char *line);
int				ft_echo(t_list *list, t_comm *comm, t_split *split);
void			ft_init(t_comm *comm);
int				ft_error(t_split *split, char *line, int error);
char			**ft_splitshell(t_split *split, char const *s, char c);
char			**ft_splitshellgt(t_split *split, char const *s, char c);
char			*ft_parsedollar(t_list *list, t_comm *comm, t_split *split,
					char *line);
void			check_quote(t_split *split, const char *c);
int				check_inverted_var(const char *c);
void			test_list(t_list *list, t_comm *comm);
void			clear_list(t_list *list, t_comm *comm);
void			free_list(void *cont);
void			free_env(void *cont);
void			free_export(void *cont);
int				parse_command(t_list *list, t_comm *comm, t_split *split);
char			*get_path(t_list *list, t_comm *comm, char *cmd, int i);
void			*ft_malloc(size_t size);
void			ft_malloc_free(t_comm *comm, char **str, int i);
int				parser_error(t_comm *comm, t_split *split, char *line);
void			ft_exit(t_list *list, t_comm *comm, t_split *split);
int				ft_pwd(t_list *list, t_comm *comm);
int				ft_cd(t_list *list, t_comm *comm, t_split *split);
int				ft_env(t_list *list, t_comm *comm, t_split *split);
int				ft_export(t_list *list, t_comm *comm, t_split *split);
size_t			export_len(char *s1, char *s2);
void			swap_list(t_list *list, t_comm *comm);
void			sort_list(t_list *list, t_comm *comm, int *swapped);
void			export_list(t_list *list, t_comm *comm, t_split *split);
void			fill_list(t_list *list, t_comm *comm, t_list *new,
					t_list *export);
void			check_export(t_list *list, t_comm *comm, t_split *split, int i);
char			**ft_superglue(t_list *list, t_comm *comm);
int				ft_unset(t_list *list, t_comm *comm, t_split *split);
void			parse_redir(t_list *list, t_comm *comm, t_split *split);
void			create_history(t_list *list, t_comm *comm, t_split *split);
void			default_sigint(int bit);
void			fork_sigint(int bit);
void			default_sigquit(int bit);
void			fork_sigquit(int bit);
void			print_user(t_comm *comm);
void			print_prompt(t_comm *comm);
char			*next_shlvl(char *shlvl);
void			ctrl_d(t_split *split);
void			galactic_env(t_comm *comm);
void			our_read_line(t_comm *comm, t_split *split);
void			fill_line(t_comm *comm, t_line *line);


#endif