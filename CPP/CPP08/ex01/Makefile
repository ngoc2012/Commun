# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/14 14:05:54 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp Span.cpp
OBJS = ${SRCS:.cpp=.o}
INCS = $(wildcard *.hpp)
MANDA = main
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA): $(SRCS) $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test:
	clear
	make re && valgrind ./$(MANDA) `shuf -i 1-10000 -n 3 | tr "\n" " "`
	#make re && valgrind ./$(MANDA) `shuf -i 1-10000 -n 5 | tr "\n" " "`
	#make re && valgrind ./$(MANDA) `shuf -i 1-10000 -n 21 | tr "\n" " "`
	#make re && ./$(MANDA) `shuf -i 1-1000000 -n 10000 | tr "\n" " "`
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
