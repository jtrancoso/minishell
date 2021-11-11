/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:25:18 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/11 18:09:57 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	default_sigint(int bit)
{
	(void)bit;
	printf("\b\b  \n");
	print_user(NULL);
}

void	fork_sigint(int bit)
{
	(void)bit;
	write(1, "\n", 1);
}

void	default_sigquit(int bit)
{
	(void)bit;
	write(1, "\b\b  \b\b", 6);
	return ;
}

void	fork_sigquit(int bit)
{
	(void)bit;
	printf("Quit: %d\n", bit);
}

void	ctrl_d(t_split *split)
{
	printf("exit\n");
	exit(split->errorcode);
}
