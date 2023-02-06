# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/02/06 01:39:14 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#LIBS = get_score.c operations.c position.c print.c rot.c cal.c cal_base.c to.c
LIBS = operations.c operations_base.c position.c print.c rot.c rot_base.c cal.c cal_base.c to_left.c to_right.c
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
	$(CC) $(FLAGS) -g $@.c $(LIBS) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I. -I./libft -I./ft_printf -I./GNL -o $(FILE)
	valgrind -q --leak-check=full ./push_swap -30 799 -806 662 -542
#	valgrind -q --leak-check=full ./push_swap 382 -867 763 89 -610 8 -600 -105 -730 818 584 48 766 852 -50 306 242 -886 403 753 322 -590 980 -894 771 -974 -162 -441 396 617 -396 -414 146 -781 -202 -139 -699 684 -149 -970 -638 699 -663 -820 -175 -434 -882 340 -634 525
norm:
	norminette $(LIBS)
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
