# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/18 17:21:13 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp
OBJS = ${SRCS:.cpp=.o}
INCS = $(wildcard *.hpp)
MANDA = find
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
%.o: %.cpp
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA): $(SRCS) $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test: all
	valgrind ./$(MANDA) 5 15 3 7 2 1 4 6 8 9
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
