# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/28 12:05:40 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = tests.cpp Account.cpp
OBJS = ${SRCS:.c=.o}
MANDA = tests
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA):
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test:
	make re && valgrind ./tests
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
