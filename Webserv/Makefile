# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/12/06 11:12:03 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main Host Server Request Response Header Configuration Location split_string is_digit itos match_wildcard
SRCS = $(addsuffix .cpp, $(addprefix srcs/, $(FILES)))
INCS = $(wildcard includes/*.hpp)
OBJS = ${SRCS:.cpp=.o}
MANDA = server
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.cpp.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.cpp=.o} -I./includes
$(MANDA): $(SRCS) $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(MANDA)
test:
	clear && make re && make clean && valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./server
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
.PHONY: all clean fclean re test
