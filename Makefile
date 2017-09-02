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

NAME    	=   ft_ls
CC      	=   gcc
RM      	=   rm -f
CFLAGS  	=  -Wall -Werror -Wextra
LIB			=	-L./lib/libft -lft
CPPFLAGS	= 	-Iincludes
SRCS		=	src/ft_settings.c \
				src/ft_settings_2.c \
				src/ft_displays.c \
				src/ft_sorts.c \
				src/ft_sorts2.c \
				src/ft_ls.c

OBJS    	=   $(SRCS:.c=.o)

all:        $(NAME)

$(NAME):    $(OBJS)
			Make -C ./lib/libft
			$(CC) -o $(NAME) $(OBJS) $(LIB) $(CPPFLAGS)
clean:
			$(RM) $(OBJS)
			Make -C ./lib/libft fclean

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

push:
			@git add .
			@echo "Enter Your Commit :"
			@read var1 ; git commit -m "$$var1"
			@echo "Enter The origin :"
			@read var2 ; git push origin "$$var2"

.PHONY:		all clean fclean re push