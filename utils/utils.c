/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:13:57 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/09 15:37:39 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *next_shlvl(char *shlvl)
{
	char *aux;
	int lvl;

	lvl = ft_atoi(shlvl) + 1;
	aux = shlvl;
	shlvl = ft_itoa(lvl);
	free (aux);
	return(shlvl);
}

void	galactic_env(t_comm *comm)
{
	int i;
	char *aux;
	char *aux2;
	char **new_split;
	t_list *new;
	t_env *env;

	i = 0;
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	comm->fixed_env[0] = ft_strdup("SHLVL=0");
	comm->fixed_env[1] = aux;
	comm->fixed_env[2] = ft_strdup("_=./minishell"); //FIXME: actualizar con el historial
	comm->fixed_env[3] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	comm->fixed_env[4] = ft_strdup("USER=unknown");
	comm->fixed_env[5] = ft_strdup("OLDPWD= ");
	comm->fixed_env[6] = NULL;
	i = 0;
	while (comm->fixed_env[i])
	{
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		//aux2 = comm.fixed_env[i];
		new_split = ft_split(comm->fixed_env[i], '=');
		new->content = env;
		((t_env*)new->content)->id = new_split[0];
		((t_env*)new->content)->value = new_split[1];
		ft_lstadd_back(&comm->env_head, new);
		free(new_split);
		//free(aux2);
		i++;
	}
	//free(comm.fixed_env);
	free(aux);
	free(aux2);
}