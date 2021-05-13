# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:59:06 by jtrancos          #+#    #+#              #
#    Updated: 2021/05/13 14:09:48 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c \
				ft_error.c \
				./parser/parser.c \
				./parser/parser_utils.c \
				./parser/ft_splitshell.c \
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
			$(CC) -fsanitize=address -L libft/ -lft  ${OBJS} -o ${NAME}
			#-fsanitize=address
		
all:		${NAME}

clean:
			${RM} ${OBJS}
			make clean -C ./libft

fclean : 	clean
			make fclean -C ./libft
			${RM} ${NAME} libft.a

re:			fclean all

.PHONY:		re all clean fclean