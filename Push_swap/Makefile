# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/01/04 13:08:23 by minh-ngu         ###   ########.fr        #
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
	$(CC) $(FLAGS) -g $@.c -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I. -I./libft -I./ft_printf -I./GNL -o $(FILE)
#	clear
#	valgrind -q --leak-check=full ./push_swap 341 445 41 -472 767
	valgrind -q --leak-check=full ./push_swap -238 981 -840 116 -816 -558 -389 632 704 910 -989 31 -246 93 -204 156 -713 21 267 397 -542 -762 -628 -944 120 -203 233 -979     34 -333 678 -678 625 -703 441 697 -278 489 641 -88 514 877 398 -399 887 990 799 -466 151 30 774 -71 -252 902 -655 -502 -89    9 -995 -340 -7 -101 708 -869 712 -596 248 -981 920 -171 -105 80 594 626 479 -943 -398 87 429 -826 -807 744 -543 -572 734 -5    55 -837 -720 706 380 768 -382 -282 -719 -22 -441 -519 -841 -834 175 -527 > test1.txt

#	valgrind -q --leak-check=full ./push_swap 42 -363 -918 -460 -116 660 91 509 -815 -706 -324 283
#	valgrind -q --leak-check=full ./push_swap 42 -363 -918 -460 -116 660 91 509 -815 -706 -324 283 -376 268 101 -499 440 242 808 -780
#	valgrind -q --leak-check=full ./push_swap 304 -52 -307 -446 232 803 -661 612 202 691 -427 -907 -777 -216 -776 103 630 987 736 -105 -374 -928 887 -718 468 507 -141 -694 680 -832 -531 -440 -276 -624 -920 351 994 271 -191 319 -300 296 33 427 459 206 -151 -706 -212 298 724 -166 -930 -457 38 -420 -8 112 -45 737 496 -589 817 -37 474 -696 -894 438 -829 -852 608 -609 -523 -184 123 -827 -64 974 -21 4 -541 414 131 -34 552 -992 228 -167 257 981 856 373 637 75 635 179 299 263 554 -995 > test1.txt
#	valgrind -q --leak-check=full ./push_swap -700 -278 -362 -767 -638 -900 739
#	valgrind -q --leak-check=full ./push_swap -713 2 -599
#	valgrind -q --leak-check=full ./push_swap 813 124 -414 850 581
#	valgrind -q --leak-check=full ./push_swap 813 124 -414 850 581 > test1.txt
#	valgrind -q --leak-check=full ./push_swap 10 -264 182 41 -243 -564 866 -970 469 -365 -474 -448 766 996 -580 902 610 66 -196 -877 -822 523 -371 877 -754 > operations.txt
#	valgrind -q --leak-check=full ./push_swap -430 806 365 630 -739 70 610 -82 -634 -609 941 -650 -716 117 469
#	valgrind -q --leak-check=full ./push_swap 105 324 198 554 712 -146 -391 718 4 -72 -467 -662 -838 -743 970 94 479 514 -978 826 -507 977 -874 -737 296 378 788 608 -336 590 813 316 -584 -362 -108 711 422 956 930 951 273 187 -815 -356 795 249 147 71 209 -759 -882 702 756 -60 462 811 -434 242 329 -69 776 737 163 -908 -658 83 157 -421 443 -623 875 112 -709 -291 -996 -314 603 -881 467 -938 461 265 -935 550 281 -404 -949 -217 -88 38 377 -219 808 -947 -192 922 -120 -87 -834 > test1.txt
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
