# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/11/08 15:33:29 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main Server ClientRequest
SRCS = $(addsuffix .cpp, $(addprefix srcs/, $(FILES)))
INCS = $(wildcard includes/*.hpp)
OBJS = ${SRCS:.cpp=.o}
MANDA = server
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(SERVER) $(CLIENT)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I./includes
$(MANDA): $(SRCS) $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(SERVER)
test:
	make re && valgrind ./server
gits:
	git add Makefile
	git add *.cpp
	git add *.hpp
	git commit -m "all"
	git push
clean:
	rm -f $(MANDA)
	rm -f $(OBJS)
fclean: clean
re: fclean all
.PHONY: all clean fclean re
