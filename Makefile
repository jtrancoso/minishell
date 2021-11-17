# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:59:06 by jtrancos          #+#    #+#              #
#    Updated: 2021/11/17 13:08:41 by jtrancos         ###   ########.fr        #
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
				./parser/ft_parsedollar_utils.c \
				./parser/parser_error.c \
				./command/parse_command.c \
				./command/parse_command_quotes.c \
				./command/parse_command_quotes2.c \
				./command/comm_utils.c \
				./command/paths.c \
				./exec/exit.c \
				./exec/pwd.c \
				./exec/cd.c \
				./exec/env.c \
				./exec/export.c \
				./exec/export_utils.c \
				./exec/unset.c \
				./exec/echo.c \
				./redir/parse_redir.c \
				./redir/redir_mgr.c \
				./signal/signal.c \
				./utils/utils.c \
				./utils/prompt.c \
				./utils/free_things.c \
				./readline/readline.c \
				./pipes/execute_pipes.c \
				./pipes/pipes.c


OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
RM			= rm -f
CFLAGS		= -Werror -Wall -Wextra

.c.o:
			${CC} -g3 -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C ./libft
			$(CC) -fsanitize=address -g -L libft/ -lft ${OBJS} -o ${NAME}
# COMPILAR MAC $(CC) -fsanitize=address -g -L libft/ -lft ${OBJS} -o ${NAME}
# COMPILAR LINUX $(CC) -fsanitize=address -g -o ${NAME} ${OBJS} -lz -L libft/ -lft -lm

all:		${NAME}

clean:
			${RM} ${OBJS}
			make clean -C ./libft

fclean : 	clean
			make fclean -C ./libft
			${RM} ${NAME} libft.a

leaks:		${OBJS}
			make -C ./libft

re:			fclean all

.PHONY:		re all clean fclean leaks