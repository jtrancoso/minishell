/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/11 12:59:37 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argv, char **argc, char **envp)
{
	char str[1024];

	write(1, "Hola soy minishell\n", 19);
	while (1)
	{
		write(1, "Nacho", 5);
		write(1, "> ", 2);
	//	ft_printf("%d\n", ft_strlen("hola"));
		//ft_printf("pwd: %s\n", getcwd(NULL, 0));
		//chdir("../cub3d");
		read(0, str, 1023);
		ft_printf("%s\n", str);
	}
	return (0);
}