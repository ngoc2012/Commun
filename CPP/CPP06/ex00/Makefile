# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/11/03 12:00:56 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp Convert.cpp
OBJS = ${SRCS:.c=.o}
MANDA = convert
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(MANDA): $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test:
	make re
	valgrind ./convert 99999999999999999999.9999
	#valgrind ./convert 0
	#valgrind ./convert 123.56
	#valgrind ./convert 1000
gits:
	git add Makefile
	git add *.cpp
	git add *.hpp
	git commit -m "all"
	git push
clean:
	rm -f $(MANDA)
fclean: clean
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
