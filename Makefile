# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milmi <milmi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/10/16 15:52:26 by milmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFT = libft.a
SRCS = main.c scan.c parser.c
FLAGS= -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT)
	$(CC) $(FLAGS) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)

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