# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/15 11:03:44 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp
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
	make re
	#./$(MANDA)
	./$(MANDA) nut dsfsdf
	./$(MANDA) nut
	./$(MANDA) input.txt
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
