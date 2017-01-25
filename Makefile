# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 21:06:34 by kacoulib          #+#    #+#              #
#    Updated: 2016/12/07 19:52:01 by kacoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  ft_ls 
HEADERS	= ft_ls.h
SOURCES = ft_ls.c
OBJ	= $(SOURCES:.c=.o)
FLAGS	= -Wall -Werror -Wextra

all: 
	gcc $(FLAGS) -c $(HEADERS) $(SOURCES)  
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cd libft && make
clean : 
	rm -rf $(OBJ) 
	cd libft && make clean 

fclean : clean
	rm -rf $(NAME)
	cd libft -rf $(NAME)
re : fclean all
	cd libft fclean all
