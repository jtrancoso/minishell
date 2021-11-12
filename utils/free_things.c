/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:02:23 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/12 14:09:34 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(void *cont)
{
	if (((t_comm *)cont)->t_word)
		free(((t_comm *)cont)->t_word);
	if (((t_comm *)cont)->t_command)
		free(((t_comm *)cont)->t_command);
	if (((t_comm *)cont)->redir.file)
		free(((t_comm *)cont)->redir.file);
	if (((t_comm *)cont)->redir.rest)
		free(((t_comm *)cont)->redir.rest);
	free((t_comm *)cont);
}

void	free_env(void *cont)
{
	if (((t_env *)cont)->id)
		free(((t_env *)cont)->id);
	if (((t_env *)cont)->value)
		free(((t_env *)cont)->value);
	free((t_env *)cont);
}

void	free_export(void *cont)
{
	if (((t_export *)cont)->id)
		free(((t_export *)cont)->id);
	if (((t_export *)cont)->value)
		free(((t_export *)cont)->value);
	free((t_export *)cont);
}
