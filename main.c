/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:22:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/05/13 13:30:13 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argv, char **argc, char **envp)
{

	t_list *head;
	t_list *list;
	t_list *new;
	//TODO: all
	
	typedef struct	s_env
	{
		char		*id;
		char		*value; 
	}				t_env;
	t_env *env;
	t_comm comm; //FIXME: lo mismo hay que alorcarla donde se use
	t_split split;
	char line[BUFFERSIZE];
	write(1, "\033[1;33m", 7);
	printf("             _            _   _             _          _ _  \n  __ _  __ _| | __ _  ___| |_(_) ___    ___| |__   ___| | | \n / _` |/ _` | |/ _` |/ __| __| |/ __|  / __| '_ \\ / _ \\ | | \n| (_| | (_| | | (_| | (__| |_| | (__   \\__ \\ | | |  __/ | | \n \\__, |\\__,_|_|\\__,_|\\___|\\__|_|\\___|  |___/_| |_|\\___|_|_| \n |___/                                                      \n\n");
	write(1, "\033[0m", 4);
	ft_init(&comm);
	char **split_env;
	head = NULL;
	int i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		split_env = ft_split(envp[i], '=');
		new->content = env;
		((t_env*)new->content)->id = split_env[0];
		((t_env*)new->content)->value = split_env[1];
		ft_lstadd_back(&head, new);
		free (split_env);
		i++;
	}
	list = head;
	char *user;
	char *pwd;
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
		ft_parseline(&comm, &split, line);
		if (ft_strncmp(line, "exit", 4) == 0)
			break;
		if (ft_strncmp(line, "pwd", 3) == 0)
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
			free(pwd);
		}
		//ret = ft_ft();
		//ft_bzero(line, BUFFERSIZE - 1);
	}
	return (0);
}
