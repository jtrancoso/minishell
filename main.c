/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/11 14:00:48 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_ft(void)
{
	ft_printf("hola\n");
	return (0);
}

int main (int argv, char **argc, char **envp)
{
	char str[1024];

	write(1, "\033[0;33m", 7);
	ft_printf("  __  __  _         _       _            _  _ \n |  \\/  |(_)       (_)     | |          | || |\n | \\  / | _  _ __   _  ___ | |__    ___ | || |\n | |\\/| || || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n | |  | || || | | || |\\__ \\| | | ||  __/| || |\n |_|  |_||_||_| |_||_||___/|_| |_| \\___||_||_|\n\n");
	write(1, "\033[0m", 4);

	/*for (char **env = envp; *env != 0; env++)
	{
		char *thisEnv = *env;
		printf("%s\n", thisEnv);
	}*/
	int ret;
	ret = 0;
	while (1)
	{
		write(1, "\033[0;34m", 7);
		write(1, "Nacho", 5);
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
		//chdir("../cub3d");
		read(0, str, 1023);
		if (ft_strncmp(str, "exit", 4) == 0)
			break;
		if (ft_strncmp(str, "pwd", 3) == 0)
			ft_printf("%s\n", getcwd(NULL, 0));
		//ret = ft_ft();
		ft_bzero(str, 1023);
	}
	return (0);
}