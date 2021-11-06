# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chicky <chicky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/11/03 15:16:35 by chicky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFT = libft.a
SRCS = main.c scan.c parser.c parser_utils.c parser_utils2.c execution.c implim_cd.c implim_pwd.c implim_export.c implim_unset.c implim_env.c implim_echo.c implim_exit.c call_exec.c pipes.c exec_redir.c
FLAGS= -g -lreadline -L /Users/sbensarg/goinfre/.brew/opt/readline/lib -I /Users/sbensarg/goinfre/.brew/opt/readline/include -Wall -Wextra -Werror 
HOMEENVFLAGS= -g -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
LINUXFLAGS= libreadline.a
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT) $(LINUXFLAGS)
	$(CC) $(LIBFT) $(SRCS) $(LIBFT) -lreadline -o $(NAME)

$(LINUXFLAGS):
	make -C readline
	cp readline/libreadline.a .
	
$(LIBFT):
	make -C libft
	cp libft/libft.a .

clean :
	
fclean : clean
	@$(rm) $(NAME)
	make -C libft fclean
	$(rm) libft.a

re: fclean all

.PHONY: all bonus both clean fclean re