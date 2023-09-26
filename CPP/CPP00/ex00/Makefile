# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/26 18:37:26 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = megaphone.cpp
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = megaphone
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.c.o:
$(MANDA):
	$(CC) $(FLAGS) -o $(MANDA)
gits:
	git add Makefile
	git add *.cpp
	git add *.h
	git commit -m "all"
	git push
clean:
	make clean -C libft
	make clean -C GNL
	make clean -C minilibx-linux
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	make fclean -C GNL	
	make clean -C minilibx-linux
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
