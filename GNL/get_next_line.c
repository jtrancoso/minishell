/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:34:48 by jtrancos          #+#    #+#             */
/*   Updated: 2020/11/30 13:02:40 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_stack(char **stack, char **line)
{
	char	*temp;

	if (ft_strchr(*stack, '\n'))
	{
		*line = ft_substr(*stack, 0, ft_strlen(*stack) -
				ft_strlen(ft_strchr(*stack, '\n')));
		temp = *stack;
		*stack = ft_strdup(ft_strchr(temp, '\n') + 1);
		free(temp);
		return (1);
	}
	else
		return (0);
}

static int	read_line(int fd, char **stack)
{
	char	*buf;
	int		bytes;
	char	*temp;

	buf = malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buf)
		return (-1);
	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (stack[fd])
		{
			temp = stack[fd];
			stack[fd] = ft_strjoin(temp, buf);
			free(temp);
		}
		else
			stack[fd] = ft_strdup(buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (bytes);
}

int			get_next_line(int fd, char **line)
{
	static char		*stack[4096];
	int				ret;

	if (fd < 0 || read(fd, stack[fd], 0) == -1 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (stack[fd])
		if (check_stack(&stack[fd], line))
			return (1);
	ret = read_line(fd, stack);
	if (ret == 0 && !stack[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (check_stack(&stack[fd], line))
		return (1);
	if (!ft_strchr(stack[fd], '\n'))
	{
		*line = ft_strdup(stack[fd]);
		free(stack[fd]);
		stack[fd] = NULL;
		return (0);
	}
	return (0);
}
