/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:13:57 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 20:24:44 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_2(t_comm *comm)
{
	comm->prev_pipe = 0;
	comm->post_pipe = 0;
	comm->prev_redir = 0;
	comm->redir.file = NULL;
	comm->redir.rest = NULL;
	comm->redir.last_fdin = 1;
	comm->redir.last_fdout = 1;
	comm->redir.t_append = 0;
	comm->redir.t_create = 0;
	comm->redir.t_trunc = 0;
	comm->dir = NULL;
	comm->home = NULL;
	comm->f_verg = 0;
}

void	ft_init(t_comm *comm)
{
	ft_init_2(comm);
	comm->t_command = NULL;
	comm->t_word = NULL;
	comm->t_pipe = 0;
	comm->t_semi = 0;
	comm->t_gt = 0;
	comm->t_gtgt = 0;
	comm->t_lt = 0;
	comm->freed = 0;
	comm->f_d = 0;
	comm->f_s = 0;
	comm->fd = 1;
	comm->export.ret = 0;
	comm->export.f_valid = 0;
	comm->export.f_exist = 0;
}

char	*next_shlvl(char *shlvl)
{
	char	*aux;
	int		lvl;

	lvl = ft_atoi(shlvl) + 1;
	aux = shlvl;
	shlvl = ft_itoa(lvl);
	free (aux);
	return (shlvl);
}

void	save_galactic_env(t_comm *comm, char **fix_env)
{
	t_list	*new;
	t_env	*env;
	char	**new_split;
	int		i;

	i = 0;
	while (fix_env[i])
	{
		new = ft_malloc(sizeof(t_list));
		env = ft_malloc(sizeof(t_env));
		new_split = ft_split(fix_env[i], '=');
		new->content = env;
		((t_env *)new->content)->id = new_split[0];
		((t_env *)new->content)->value = new_split[1];
		ft_lstadd_back(&comm->env_head, new);
		free(new_split);
		i++;
	}
}

void	galactic_env(t_comm *comm)
{
	char	*aux;
	char	*aux2;
	char	**fix_env;

	fix_env = ft_malloc(sizeof(char **) * 6);
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	fix_env[0] = ft_strdup("SHLVL=0");
	fix_env[1] = aux;
	fix_env[2] = ft_strdup("_=./minishell");
	fix_env[3] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	fix_env[4] = ft_strdup("OLDPWD= ");
	fix_env[5] = NULL;
	save_galactic_env(comm, fix_env);
	ft_malloc_free(fix_env, 0);
	free(aux2);
}
