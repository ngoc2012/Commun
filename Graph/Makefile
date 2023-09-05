# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/02 17:12:33 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBML = minilibx-linux/libft_Linux.a
INCL_MINILIBX = -I./minilibx-linux
OBJ_MINILIBX = -L./minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz
LIBS = libft
all:	$(MANDA)
$(LIBFT):
	make -C libft
$(LIBML):
	make -C minilibx-linux
.c.o:
	$(CC) $(FLAGS) $(INCL_MINILIBX) -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):	$(MOBJ) $(LIBFT) $(LIBML) 
	$(CC) $(FLAGS) $(MOBJ) $(OBJ_MINILIBX) -L./libft -lft -o $(MANDA)
bonus:	$(MANDA)
norm:
	norminette $(LIBS) srcs includes
gits:
	git add Makefile
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.c, $(LIBS) srcs)
	git add $(addsuffix /*.h, $(LIBS) includes)
	git commit -m "all"
	git push
clean:
	make clean -C libft
	make clean -C minilibx-linux
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	make clean -C minilibx-linux
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
