# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/21 07:37:30 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = push_swap
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
$(FILE): $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) *.c -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I. -I./libft -I./ft_printf -I./GNL -o $(FILE)
	clear
	valgrind -q --leak-check=full ./push_swap -33 -22 -55 1 3 6 5 -8
	valgrind -q --leak-check=full ./push_swap -33 -22 -55 1 3 6 5 -8
#	./push_swap -33 -22 1 3 6 5 -8
#	./push_swap -22 1 3 6 5 -8
#	./push_swap 2 1 3 6 5 8
#	./push_swap 2 1 3 14 6 5 0 8
#	valgrind -q --leak-check=full ./push_swap 2 1 3 6 5 8
#	valgrind -q --leak-check=full ./push_swap 2 1 3 14 6 5 0 8
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
