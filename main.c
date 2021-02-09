/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/09 14:23:26 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main (int argv, char **argc, char **envp)
{
	char str[1024];

	write(1, "Hola soy minishell\n", 19);
	while (1)
	{
		write(1, "Nacho", 5);
		write(1, "> ", 2);
		chdir("../cub3d");
		printf("%s\n", getcwd(NULL, 0));
		read(0, str, 1023);
	}
	return (0);
}