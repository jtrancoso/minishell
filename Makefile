# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:59:06 by jtrancos          #+#    #+#              #
#    Updated: 2021/06/10 13:46:37 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c \
				ft_error.c \
				test_list.c \
				./parser/parser.c \
				./parser/parser_utils.c \
				./parser/ft_splitshell.c \
				./parser/ft_splitshellgt.c \
				./parser/ft_parsedollar.c \
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
			$(CC) -fsanitize=address -g -L libft/ -lft  ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}
			make clean -C ./libft

fclean : 	clean
			make fclean -C ./libft
			${RM} ${NAME} libft.a

leaks:		${OBJS}
			make -C ./libft
			$(CC) -L libft/ -lft  ${OBJS} -o ${NAME}

re:			fclean all

.PHONY:		re all clean fclean leaks