/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:43:43 by jtrancos          #+#    #+#             */
/*   Updated: 2021/04/09 19:33:04 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_comm *comm, char *line)
{
	int	i;

	i = 0;
	//printf("%d\n", line[ft_strlen(line - 1)]);
	if (line[0] == '-' && line[1] == 'n')
	{
		comm->echo.flag_n = 1;
		i = 2;
		while (ft_isspace(line[i]))
			i++;
	}
	//printf("hola\n");
	printf("%s\n", line);
	/*if (comm->echo.flag_n == 0)
		ft_printf("\n");*/
	return (0);
}
