# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/25 21:01:12 by minh-ngu         ###   ########.fr        #
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
	$(CC) $(FLAGS) -g *.c -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I. -I./libft -I./ft_printf -I./GNL -o $(FILE)
	clear
	valgrind -q --leak-check=full ./push_swap 42 -363 -918 -460 -116 660 91 509 -815 -706 -324 283 -376 268 101 -499 440 242 808 -780
#	valgrind -q --leak-check=full ./push_swap -430 806 365 630 -739 70 610 -82 -634 -609 941 -650 -716 117 469
#	valgrind -q --leak-check=full ./push_swap 105 324 198 554 712 -146 -391 718 4 -72 -467 -662 -838 -743 970 94 479 514 -978 826 -507 977 -874 -737 296 378 788 608 -336 590 813 316 -584 -362 -108 711 422 956 930 951 273 187 -815 -356 795 249 147 71 209 -759 -882 702 756 -60 462 811 -434 242 329 -69 776 737 163 -908 -658 83 157 -421 443 -623 875 112 -709 -291 -996 -314 603 -881 467 -938 461 265 -935 550 281 -404 -949 -217 -88 38 377 -219 808 -947 -192 922 -120 -87 -834
#	bash test.sh
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
