/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/04/07 12:10:59 by jtrancos         ###   ########.fr       */
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
	int ret;
	t_env *env;
	t_comm comm;
	char line[BUFFERSIZE];
	write(1, "\033[1;33m", 7);
	printf("             _            _   _             _          _ _  \n  __ _  __ _| | __ _  ___| |_(_) ___    ___| |__   ___| | | \n / _` |/ _` | |/ _` |/ __| __| |/ __|  / __| '_ \\ / _ \\ | | \n| (_| | (_| | | (_| | (__| |_| | (__   \\__ \\ | | |  __/ | | \n \\__, |\\__,_|_|\\__,_|\\___|\\__|_|\\___|  |___/_| |_|\\___|_|_| \n |___/                                                      \n\n");
	write(1, "\033[0m", 4);
	ft_init(&comm);
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
	list = head;
	char *user;
	while (list)
	{
		if (ft_strncmp(((t_env*)list->content)->id, "USER", 4) == 0)
			user = ft_strdup(((t_env*)list->content)->value);
		list = list->next;
	}

	while (1)
	{
		ft_bzero(line, BUFFERSIZE - 1);
		write(1, "\033[1;36m", 7);
		write(1, user , ft_strlen(user));
		write(1, "> ", 2);
		//write(1, user, ft_strlen(user));
		//write(1, "> \n", 2);
		write(1, "\033[0m", 4);
		//chdir("../cub3d");
		read(0, line, BUFFERSIZE - 1);
		ft_parseline(&comm, line);
		if (ft_strncmp(line, "exit", 4) == 0)
			break;
		if (ft_strncmp(line, "pwd", 3) == 0)
			printf("%s\n", getcwd(NULL, 0));
		//ret = ft_ft();
		//ft_bzero(line, BUFFERSIZE - 1);
	}
	return (11);
}
