# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:59:06 by jtrancos          #+#    #+#              #
#    Updated: 2021/02/15 16:21:19 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c\
				./parser/parser.c\
				./parser/parser_utils.c\
				echo.c


OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
RM			= rm -f
#CFLAGS		= -fsanitize=address -g3

.c.o:
			${CC} -g3 -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C ./libft
			make -C ./printf
			$(CC) -L printf/ -lftprintf -L libft/ -lft -fsanitize=address ${OBJS} -o ${NAME}
		
all:		${NAME}

clean:
			${RM} ${OBJS}
			make clean -C ./libft
			make clean -C ./printf


fclean : 	clean
			make fclean -C ./printf
			make fclean -C ./libft
			${RM} ${NAME} libftprintf.a libft.a

re:			fclean all

.PHONY:		re all clean fclean