# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/16 11:10:26 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp PmergeMe.cpp
OBJS = ${SRCS:.cpp=.o}
INCS = $(wildcard *.hpp)
MANDA = PmergeMe
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA): $(SRCS) $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test:
	clear
	make re
	valgrind ./PmergeMe `shuf -i 1-10000 -n 1 | tr "\n" " "`
	valgrind ./PmergeMe `shuf -i 1-10000 -n 2 | tr "\n" " "`
	valgrind ./PmergeMe `shuf -i 1-100000 -n 11 | tr "\n" " "`
	valgrind ./PmergeMe 0 `shuf -i 1-10000 -n 10 | tr "\n" " "` 1000
	valgrind ./PmergeMe `shuf -i 1-10000 -n 21 | tr "\n" " "`
	bash test.sh
	make clean
gits:
	git add Makefile
	git add *.cpp
	git add *.hpp
	git commit -m "all"
	git push
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
