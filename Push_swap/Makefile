# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/02/02 11:24:07 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#LIBS = get_score.c operations.c position.c print.c rot.c cal.c cal_base.c to.c
LIBS = operations.c operations_base.c position.c print.c rot.c rot_base.c cal.c cal_base.c to.c
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
