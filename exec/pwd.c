/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:35:42 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/25 13:41:30 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_list *list, t_comm *comm)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, comm->redir.last_fdout);
	ft_putchar_fd('\n', comm->redir.last_fdout);
	free(pwd);
}