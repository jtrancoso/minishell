/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/13 13:27:35 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argv, char **argc, char **envp)
{

	/*typedef struct	s_list
	{
	void			*content;
	struct s_list	*next;
	}				t_list;*/
	t_list *head;
	t_list *list;
	t_list *new;
	
	typedef struct	s_env
	{
		char		*id;
		char		*value;
	}				t_env;
	t_env *env;

	char str[4096];

	write(1, "\033[0;33m", 7);
	ft_printf("             _            _   _             _          _ _  \n  __ _  __ _| | __ _  ___| |_(_) ___    ___| |__   ___| | | \n / _` |/ _` | |/ _` |/ __| __| |/ __|  / __| '_ \\ / _ \\ | | \n| (_| | (_| | | (_| | (__| |_| | (__   \\__ \\ | | |  __/ | | \n \\__, |\\__,_|_|\\__,_|\\___|\\__|_|\\___|  |___/_| |_|\\___|_|_| \n |___/                                                      \n\n");
	write(1, "\033[0m", 4);


	char **split;
	head = NULL;
	int i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		split = ft_split(envp[i], '=');
		new->content = env;
		((t_env*)new->content)->id = split[0];
		((t_env*)new->content)->value = split[1];
		ft_lstadd_back(&head, new);
		free (split);
		i++;
	}
	while (1)
	{
		write(1, "\033[0;35m", 7);
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
		ft_bzero(str, 4095);
	}
	return (0);
}