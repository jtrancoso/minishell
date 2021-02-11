# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:59:06 by jtrancos          #+#    #+#              #
#    Updated: 2021/02/11 12:37:49 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c


OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
RM			= rm -f
#CFLAGS		= -Werror -Wall -Wextra

.c.o:
			${CC} -g -c $< -o ${<:.c=.o} ${CFLAGS}

${NAME}:	${OBJS}
			${MAKE} -C ./printf
			$(CC) -L printf/ -lftprintf $^ -o ${NAME}
		
all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./printf

fclean : 	clean
			${RM} ${NAME} libftprintf.a libft.a

re:			fclean all

.PHONY:		re all clean fclean