/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:35:42 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/27 12:14:46 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_list *list, t_comm *comm)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}