# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/03/13 21:25:34 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS1 = client.c
MSRC1 = $(addprefix srcs/, $(SRCS1))
MOBJ1 = ${MSRC1:.c=.o}
MANDA1 = client
SRCS2 = server.c
MSRC2 = $(addprefix srcs/, $(SRCS2))
MOBJ2 = ${MSRC2:.c=.o}
MANDA2 = server
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBPR = ft_printf/libftprintf.a
LIBS = libft ft_printf
all:	$(MANDA1) $(MANDA2)
$(LIBFT):
	make -C libft
$(LIBPR):
	make -C ft_printf
.c.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA1):	$(MOBJ1) $(LIBFT) $(LIBPR)
	$(CC) $(FLAGS) $(MOBJ1) -L./libft -lft -L./ft_printf -lftprintf -o $(MANDA1)
$(MANDA2):	$(MOBJ2) $(LIBFT) $(LIBPR)
	$(CC) $(FLAGS) $(MOBJ2) -L./libft -lft -L./ft_printf -lftprintf -o $(MANDA2)
bonus:	$(MANDA1) $(MANDA2)
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
	make clean -C libft
	make clean -C ft_printf
	rm -f $(MOBJ1) $(MOBJ2)
fclean: clean
	make fclean -C libft	
	make fclean -C ft_printf
	rm -f $(MANDA1) $(MANDA2)
re: fclean all
.PHONY: all clean fclean re
