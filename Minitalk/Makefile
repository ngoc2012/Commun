# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/03/06 11:15:29 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = srcs/server.c
SERVER = $(LIBS)
CLIENT = srcs/client.c
BONUS = $(LIBS) srcs/checker.c
FILE = server client
CC = cc
FLAGS = -Wall -Wextra -Werror
GNL = libftgnl.a
LIBFT = libft.a
LIBPR = libftprintf.a
all: $(FILE)
$(LIBFT):
	make -C libft
$(LIBPR):
	make -C ft_printf
$(GNL):
	make -C GNL
server: $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) $(SERVER) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I./includes -I./libft -I./ft_printf -I./GNL -o server
client: $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) $(CLIENT) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I./includes -I./libft -I./ft_printf -I./GNL -o client
bonus: $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) -g $(BONUS) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I./includes -I./libft -I./ft_printf -I./GNL -o checker
check:
	valgrind -q --leak-check=full ./checker
test:
	make server && make client && ./server
#	make server && make client && ./server
#	make server && make client && valgrind -q --leak-check=full ./server
norm:
	norminette $(MANDA) includes/*.h
	norminette $(BONUS) includes/*.h
clean:
	make clean -C GNL
	make clean -C libft
	make clean -C ft_printf
	rm -f *.o
fclean: clean
	make fclean -C GNL
	make fclean -C libft	
	make fclean -C ft_printf
	rm -f $(FILE)
re: fclean all
