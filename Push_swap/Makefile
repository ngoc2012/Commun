# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/03/08 09:27:24 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = push_swap.c get_arg.c get_args.c operations.c operations_base.c position.c print.c rot.c rot_base.c cal.c cal_base.c to_left.c to_right.c
MSRC = $(addprefix srcs/, $(SRCS) main.c)
BSRC = $(addprefix srcs/, $(SRCS) checker.c)
MOBJ = ${MSRC:.c=.o}
BOBJ = ${BSRC:.c=.o}
MANDA = push_swap
BONUS = checker
CC = cc
FLAGS = -Wall -Wextra -Werror
GNL = GNL/libftgnl.a
LIBFT = libft/libft.a
LIBPR = ft_printf/libftprintf.a
LIBS = GNL libft ft_printf
all: $(MANDA)
$(LIBFT):
	make -C libft
$(LIBPR):
	make -C ft_printf
$(GNL):
	make -C GNL
.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA): $(MOBJ) $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) $(MOBJ) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -o $(MANDA)
bonus:	$(BONUS)
$(BONUS): $(BOBJ) $(LIBFT) $(LIBPR) $(GNL)
	$(CC) $(FLAGS) $(BOBJ) -L./libft -lft -L./ft_printf -lftprintf -L./GNL -lftgnl -o $(BONUS)
norm:
	norminette $(LIBS) srcs includes
git:
	git add Makefile
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.c, $(LIBS) srcs)
	git add $(addsuffix /*.h, $(LIBS) includes)
	git commit -m "all"
	git push
clean:
	make clean -C GNL
	make clean -C libft
	make clean -C ft_printf
	rm -f $(MOBJ) $(BOBJ)
fclean: clean
	make fclean -C GNL
	make fclean -C libft	
	make fclean -C ft_printf
	rm -f $(MANDA) $(BONUS)
re: fclean all
.PHONY: all clean fclean re
