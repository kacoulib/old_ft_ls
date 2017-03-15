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
SOURCES = src/ft_ls.c src/settings/ft_settings.c src/settings/ft_settings_2.c src/displays/ft_displays.c src/displays/ft_displays_2.c src/sortings/ft_sorts.c
OBJ	= $(SOURCES:.c=.o)
FLAGS	= -Wall -Werror -Wextra

all: 
	gcc $(FLAGS) -c $(HEADERS) $(SOURCES)  
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME) && chmod 755 $(NAME)
	cd libft && make
clean : 
	rm -rf $(OBJ) 
	cd lib/libft && make clean 

fclean : clean
	rm -rf $(NAME)
	cd lib/libft -rf $(NAME)
re : fclean all
	cd lib/libft fclean all
