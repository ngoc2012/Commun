# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/28 10:27:40 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp
OBJS = ${SRCS:.c=.o}
MANDA = test
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA):
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
gits:
	git add Makefile
	git add *.cpp
	git add *.hpp
	git commit -m "all"
	git push
test0:
	make re && valgrind --track-fds=yes ./test text Lorem French
	cat text
	echo "=============================================================="
	cat text.replace
clean:
	rm -f $(MANDA)
fclean: clean
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
