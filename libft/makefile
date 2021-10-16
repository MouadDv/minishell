# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milmi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2019/11/10 00:43:16 by milmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SRCS = ft_strtrim.c ft_substr.c ft_calloc.c ft_itoa.c ft_substr.c ft_strmapi.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_isalnum.c\
		ft_isascii.c  ft_memccpy.c  ft_atoi.c ft_strnstr.c ft_strrchr.c ft_memcpy.c ft_memmove.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_calloc.c\
		ft_strdup.c ft_isprint.c    ft_memset.c ft_strncmp.c    ft_toupper.c ft_bzero.c ft_isalpha.c ft_isdigit.c ft_memchr.c ft_strlen.c ft_tolower.c  ft_strjoin.c\
		ft_strtrim.c ft_split.c ft_itoa.c

BS = ft_lstmap_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstnew_bonus.c
OBJECTS = $(SRCS:.c=.o)
OBJECTS_BS = $(BS:.c=.o)
INCLUDES=./
all: $(NAME)
$(NAME): $(SRCS) libft.h
	gcc -Wall -Wextra -Werror -I $(INCLUDES) -c $(SRCS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
bonus:
	gcc -Wall -Wextra -Werror -I $(INCLUDES) -c $(BS)
	ar rc $(NAME) $(OBJECTS_BS)
	ranlib $(NAME)
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_BS)
fclean: clean
	rm -f $(NAME)
re:	fclean all
