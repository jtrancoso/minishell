/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:20:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/10 10:40:46 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_user(t_comm *comm)
{
	(void)comm;
	write(1, "\033[1;36m", 7);
	write(1, "galactic", 8);
	write(1, "> ", 2);
	write(1, "\033[0m", 4);
}

void	print_prompt(t_comm *comm)
{
	write(1, "\033[1;33m", 7);
	write(1, ART, ft_strlen(ART));
	write(1, "\033[0m", 4);
	print_user(comm);
}
