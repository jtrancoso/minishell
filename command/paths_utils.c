/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:42:47 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 12:43:27 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_free_aux(char *real_path, char *aux_cmd)
{
	char	*str;

	str = ft_strdup(real_path);
	free(real_path);
	free(aux_cmd);
	return (str);
}

void	free_aux(char *aux_cmd, char **paths)
{
	free(paths);
	free(aux_cmd);
}
