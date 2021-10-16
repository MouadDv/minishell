# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milmi <milmi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/06/07 16:59:48 by milmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
SRCS = main.c scan.c
FLAGS= -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT)
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean :
	
fclean : clean
	@$(rm) $(NAME)

re: fclean all

.PHONY: all bonus both clean fclean re