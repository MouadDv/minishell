# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milmi <milmi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/11/25 05:56:42 by milmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFT = libft.a
SRCS = call_exec.c call_exec_utils.c data_proccessing.c data_proccessing_utils.c \
		env_strct.c exec_redir.c exec_redir_norm.c exec_redir_norm2.c execution.c \
		free.c impim_export_utils2.c implim_cd.c implim_echo.c implim_env.c implim_exit.c \
		implim_export.c implim_export_utils.c implim_unset.c implim_pwd.c main.c parser.c \
		parser_utils.c parser_utils2.c parser_utils3.c pipes.c pipes_norm.c print_strct.c \
		rmquotes.c scan.c exec_redir_norm3.c GNL/get_next_line.c GNL/get_next_line_norm.c \
		GNL/get_next_line_utils.c heredoc_utils.c pipes_norm2.c
READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
FLAGS= -Wall -Wextra -Werror -fsanitize=address
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(SRCS) $(LIBFT) minishell.h
	@$(CC) $(LIBFT) $(SRCS) $(READLINE) $(FLAGS) -o $(NAME)

$(LIBFT):
	@make -C libft
	@cp libft/libft.a .

valgrind: fclean $(LIBFT)
	$(CC) $(VALGRIND) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)
	valgrind --leak-check=full ./minishell

clean :
	@make -C libft clean
	
fclean : clean
	@$(rm) $(NAME)
	@make -C libft fclean
	@$(rm) libft.a

re: fclean all

.PHONY: all clean fclean re