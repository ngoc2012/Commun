# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/11/05 22:01:55 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.cpp srcs/Server.cpp
SRCS2 = srcs/client.cpp
OBJS = ${SRCS:.cpp=.o}
OBJS2 = ${SRCS2:.cpp=.o}
SERVER = server
CLIENT = client
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(SERVER) $(CLIENT)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I./includes
$(SERVER): $(SRCS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(SERVER)
$(CLIENT): $(SRCS2) $(OBJS2)
	$(CC) $(FLAGS) $(OBJS2) -o $(CLIENT)
test:
	make re && valgrind ./server
gits:
	git add Makefile
	git add *.cpp
	git add *.hpp
	git commit -m "all"
	git push
clean:
	rm -f $(SERVER) $(CLIENT)
fclean: clean
re: fclean all
.PHONY: all clean fclean re
