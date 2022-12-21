# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/21 08:06:14 by minh-ngu         ###   ########.fr        #
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
	valgrind -q --leak-check=full ./push_swap 95 -405 -995 -349 -633 657 663 -55 -369 329 -588 250 723 527 -541 56 -849 -899 -58 307 789 586 943 853 -337 798 619 344 716 763 75 -366 -609 811 -961 257 459 79 -628 953 76 -233 -895 -487 -370 -269 546 -635 -384 -760 212 -467 662 -205 819 726 634 -851 859 821 -25 -456 -695 575 -792 373 -224 119 445 997 792 -518 51 877 769 593 94 132 304 -12 81 -873 620 -622 35 736 -757 -920 -364 -315 -516 778 63 317 -706 927 -453 614 -21 -292
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
