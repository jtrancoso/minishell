/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/13 07:45:38 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*point_path(t_split *split, char *cmd)
{
	char	*aux;
	char	*expand;

	aux = getcwd(NULL, 0);
	expand = ft_strjoin(aux, cmd + 1);
	free (aux);
	return (expand);
}

void	clean_quotes(t_list *list, t_comm *comm, t_split *split)
{
	char **aux;
	int i;
	int j;
	int k;
	int l;
	char *str;
	int s_quote;
	int d_quote;
	int	bar;

	i = 0;
	j = 0;
	while (comm->cmd.cmd[i])
		i++;
	aux = ft_malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (comm->cmd.cmd[i])
	{
		l = 0;
		k = 0;
		aux[j] = ft_malloc(sizeof(char *) * (ft_strlen(comm->cmd.cmd[i])) + 1);
		while (comm->cmd.cmd[i][k])
		{
			if (s_quote % 2 == 0 && d_quote % 2 == 0)
			{
				if (comm->cmd.cmd[i][k] == '\\')
				{
					k++;
					if (comm->cmd.cmd[i][k] == '\\' || comm->cmd.cmd[i][k] == '\'' || comm->cmd.cmd[i][k] == '\"' || comm->cmd.cmd[i][k] == '~')
						{
							aux[j][l] = comm->cmd.cmd[i][k];
							l++;
							if (comm->cmd.cmd[i][k + 1] == '~')
								comm->f_verg = 1;
						}
				}
				else if (comm->cmd.cmd[i][k] == '\'')
				{
					s_quote++;
					if (comm->cmd.cmd[i][k + 1] == '~')
						comm->f_verg = 1;
				}
				else if (comm->cmd.cmd[i][k] == '\"')
				{
					d_quote++;
					if (comm->cmd.cmd[i][k + 1] == '~')
						comm->f_verg = 1;
				}
				else
				{
					aux[j][l] = comm->cmd.cmd[i][k];
					l++;
				}
			}
			else if (s_quote % 2 != 0)
			{
				if (comm->cmd.cmd[i][k] == '\'')
					s_quote++;
				else
				{
					aux[j][l] = comm->cmd.cmd[i][k];
					l++;
				}	
			}
			else if (d_quote % 2 != 0)
			{
				if (comm->cmd.cmd[i][k] == '\\')
				{
					k++;
					if (comm->cmd.cmd[i][k] == '\'' || (comm->cmd.cmd[i][k] != '\\' && comm->cmd.cmd[i][k] != '\"'))
					{
							aux[j][l] = '\\';
							l++;
							aux[j][l] = comm->cmd.cmd[i][k];
							l++;
					}
					else if (comm->cmd.cmd[i][k] == '\\' || comm->cmd.cmd[i][k] == '\"')
						{
							aux[j][l] = comm->cmd.cmd[i][k];
							l++;
						}
				}
				else if (comm->cmd.cmd[i][k] == '\"')
					d_quote++;
				else
				{
					aux[j][l] = comm->cmd.cmd[i][k];
					l++;
				}
			}
			k++;
		}
		aux[j][l] = '\0';
		i++;
		j++;
	}
	aux[j] = NULL;
	i = 0;
	while (aux[i])
	{
		str = ft_strdup(comm->cmd.cmd[i]);
		free(comm->cmd.cmd[i]);
		comm->cmd.cmd[i] = aux[i];
		free(str);
		i++;
	}
	ft_malloc_free(comm, aux, j);
}

int	check_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	else if (cmd[0] == '.' && cmd[1] == '/')
		return(3);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "pwd", 3) == 0)
		return(2);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "echo", 4) == 0)
		return(2);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "exit", 4) == 0)
		return(2);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "env", 3) == 0)
		return(2);
	else if (ft_strlen(cmd) == 2 && ft_strncmp(cmd, "cd", 2) == 0)
		return(2);
	else if (ft_strlen(cmd) == 5 && ft_strncmp(cmd, "unset", 5) == 0)
		return(2);
	else if (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", 6) == 0)
		return(2);
	return (0);
}

int	exec_comm(t_list *list, t_comm *comm, t_split *split)
{
	if (ft_strncmp(comm->cmd.path, "pwd", 3) == 0)
		return (ft_pwd(list, comm));
	else if (ft_strncmp(comm->cmd.path, "echo", 4) == 0)
		return(ft_echo(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "exit", 4) == 0)
		ft_exit(list, comm, split);
	else if (ft_strncmp(comm->cmd.path, "env", 3) == 0)
		return(ft_env(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "cd", 2) == 0)
		return(ft_cd(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "unset", 5) == 0)
		return(ft_unset(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "export", 6) == 0)
		return(ft_export(list, comm, split));
	return (0);
}

int	parse_command(t_list *list, t_comm *comm, t_split *split)
{
	t_list *env_list;
	int	status;
	char **cmd;
	char *path;
	char **env_array;

	comm->cmd.cmd = ft_splitshell(split, ((t_comm *)list->content)->t_command, ' ');
	int i = 0;
	while (comm->cmd.cmd[i])
		i++;
	create_history(list, comm, split);
	comm->cmd.env_array = ft_superglue(list, comm);
	clean_quotes(list, comm, split);
	if (comm->cmd.cmd[0])
	{
		if (!check_path(comm->cmd.cmd[0]))
			comm->cmd.path = get_path(list, comm, comm->cmd.cmd[0], -1);
		else if (check_path(comm->cmd.cmd[0]) == 1)
			comm->cmd.path = ft_strdup(comm->cmd.cmd[0]);
		else if (check_path(comm->cmd.cmd[0]) == 3)
			comm->cmd.path = point_path(split, comm->cmd.cmd[0]);
		else
		{
			comm->cmd.path = ft_strdup(comm->cmd.cmd[0]);
			split->errorcode = exec_comm(list, comm, split);
		}
		if (check_path(comm->cmd.cmd[0]) != 2)
		{
			status = 0;
			env_list = comm->env_head;
			list = comm->parse_head;
			comm->pid = fork();
			if (comm->pid == 0)
			{
				if (execve(comm->cmd.path, comm->cmd.cmd, comm->cmd.env_array) != 0)
					exit(ft_error(split, comm->cmd.cmd[0], 4));
			}
			else
			{
				wait(&status);
				split->errorcode = status >> 8; //BRUJERIA
			}
		}
		free(comm->cmd.path);
		ft_malloc_free(comm, comm->cmd.cmd, 0);
		ft_malloc_free(comm, comm->cmd.env_array, 0);
	}
	return(0);
}