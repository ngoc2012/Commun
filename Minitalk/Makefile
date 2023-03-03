# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/03/02 22:04:40 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = srcs/server.c
SERVER = $(LIBS)
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
bonus: $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) -g $(BONUS) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -I./includes -I./libft -I./ft_printf -I./GNL -o checker
check:
	valgrind -q --leak-check=full ./checker
	valgrind -q --leak-check=full ./checker 3
	valgrind -q --leak-check=full ./checker 3 2 1 0 1000000000000
	valgrind -q --leak-check=full ./checker 3 2 1 0 MAX_INT
	valgrind -q --leak-check=full ./checker 3 2 one 0
	valgrind -q --leak-check=full ./checker "" 1
	valgrind -q --leak-check=full ./checker 3 2 1 0 0
	valgrind -q --leak-check=full ./push_swap 42
	valgrind -q --leak-check=full ./push_swap 0 1 2 3
	valgrind -q --leak-check=full ./push_swap 0 1 2 3 4 5 6 7 8 9
	valgrind -q --leak-check=full ./push_swap 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	ARG="4 67 3 87 23"; ./push_swap $$ARG | valgrind -q --leak-check=full ./checker $$ARG
	ARG="382 -867 763 89 -610 8 -600 -105 -730 818 584 48 766 852 -50 306 242 -886 403 753 322 -590 980 -894 771 -974 -162 -441 396 617 -396 -414 146 -781 -202 -139 -699 684 -149 -970 -638 699 -663 -820 -175 -434 -882 340 -634 525 4 67 3 87 23"; ./push_swap $$ARG | valgrind -q --leak-check=full ./checker $$ARG
test:
	make -i check
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
