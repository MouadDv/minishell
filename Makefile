# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milmi <milmi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/10/21 19:16:27 by milmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFT = libft.a
SRCS = main.c scan.c parser.c parser_utils.c
FLAGS= -g -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
HOMEENVFLAGS= -g -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT)
	$(CC) $(HOMEENVFLAGS) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)

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