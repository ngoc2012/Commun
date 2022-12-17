# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/17 14:35:19 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = push_swap
CC = cc
FLAGS = -Wall -Wextra -Werror
GNL = libftgnl.a
LIBFT = libft.a
LIBPR = libftprintf.a
all: $(FILE)
$(GNL):
	make -C GNL
$(LIBFT):
	make -C libft
$(LIBPR):
	make -C ft_printf
$(FILE): $(LIBFT) $(LIBPR)
	$(CC) $(FLAGS) *.c -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I. -I./libft -I./ft_printf -I./GNL -o $(FILE)
	./push_swap 2 1 3 6 5 8
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
