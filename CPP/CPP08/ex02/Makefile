# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/14 15:29:41 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp
TEMP = MutantStack.tpp
OBJS = ${SRCS:.cpp=.o}
INCS = $(wildcard *.hpp)
MANDA = main
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
%.o: %.cpp $(TEMP)
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA): $(SRCS) $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test:
	clear
	make re
	valgrind ./$(MANDA)
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
