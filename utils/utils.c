/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:13:57 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/10 16:14:27 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
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

	fix_env = malloc(sizeof(char **) * 6);
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	fix_env[0] = ft_strdup("SHLVL=0");
	fix_env[1] = aux;
	fix_env[2] = ft_strdup("_=./minishell");
	fix_env[3] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	fix_env[4] = ft_strdup("OLDPWD= ");
	fix_env[5] = NULL;
	save_galactic_env(comm, fix_env);
	ft_malloc_free(comm, fix_env, 0);
	free(aux2);
}
