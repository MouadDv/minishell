# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/11/09 14:07:48 by sbensarg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFT = libft.a
SRCS = main.c scan.c parser.c parser_utils.c parser_utils2.c execution.c implim_cd.c implim_pwd.c implim_export.c implim_unset.c implim_env.c implim_echo.c implim_exit.c call_exec.c pipes.c exec_redir.c pipes_norm.c exec_redir_norm.c exec_redir_norm2.c implim_export_utils.c impim_export_utils2.c call_exec_utils.c
FLAGS= -g -lreadline -L /Users/sbensarg/.brew/opt/readline/lib -I /Users/sbensarg/.brew/opt/readline/include -Wall -Wextra -Werror 
HOMEENVFLAGS= -g -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
LINUXFLAGS= libreadline.a
rm = rm -f
CC = gcc

all : $(NAME)
#  $(LINUXFLAGS)
$(NAME) : $(LIBFT)
	$(CC) $(LIBFT) $(SRCS) $(LIBFT) $(FLAGS) -o $(NAME)

# $(LINUXFLAGS):
# 	make -C readline
# 	cp readline/libreadline.a .
	
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