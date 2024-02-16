# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/16 10:20:14 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp RPN.cpp
OBJS = ${SRCS:.cpp=.o}
INCS = $(wildcard *.hpp)
MANDA = RPN
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
	./$(MANDA) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(MANDA) "7 7 * 7 -"
	./$(MANDA) "1 2 * 2 / 2 * 2 4 - +"
	./$(MANDA) "1 1 +"
	./$(MANDA) "1 1 + +"
	./$(MANDA) "(1 + 1)"
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
