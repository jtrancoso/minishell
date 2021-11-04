/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:25:18 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/04 17:26:41 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_user(t_comm *comm)
{
	(void)comm;
	write(1, "\033[1;36m", 7);
	write(1, "galactic" , 8);
	write(1, "> ", 2);
	write(1, "\033[0m", 4);
}

void	default_sigint(int bit)
{
	(void)bit;
	printf("\b\b  \n");
	print_user(NULL);
}

void fork_sigint(int bit)
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