# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/11/02 04:49:51 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/server.cpp
SRCS2 = srcs/client.cpp
OBJS = ${SRCS:.c=.o}
OBJS2 = ${SRCS2:.c=.o}
SERVER = server
CLIENT = client
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(SERVER) $(CLIENT)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I.
$(SERVER): $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o $(SERVER)
$(CLIENT): $(SRCS2)
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
