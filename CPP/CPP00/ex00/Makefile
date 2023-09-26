# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/26 18:41:54 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = megaphone.cpp
MANDA = megaphone
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) $(INCL_MINILIBX) -g -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):
	$(CC) $(FLAGS) $(SRCS) -o $(MANDA)
gits:
	git add Makefile
	git add *.cpp
	git add *.h
	git commit -m "all"
	git push
clean:
	rm -f $(MANDA)
fclean: clean
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
