# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/04/06 12:52:44 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = init.c init_fract.c data.c events.c move_v.c move_h.c keys.c color.c cal.c sier.c draw.c fract-ol.c
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = fract-ol
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBPR = ft_printf/libftprintf.a
LIBS = libft ft_printf
#INCL_MINILIBX = -I/usr/local/include -lmlx_Linux -O3
#OBJ_MINILIBX = -L/usr/local/lib -lmlx_Linux -lXext -lX11 -lm -lz
INCL_MINILIBX = -I./minilibx-linux
OBJ_MINILIBX = -L./minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz
all:	$(MANDA)
$(LIBFT):
	make -C libft
$(LIBPR):
	make -C ft_printf
.c.o:
	$(CC) $(FLAGS) $(INCL_MINILIBX) -D CX=-0.7269 -D CY=0.1889 -D MIN_ITER=50 -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):	$(MOBJ) $(LIBFT) $(LIBPR)
	$(CC) $(FLAGS) $(MOBJ) $(OBJ_MINILIBX) -L./libft -lft -L./ft_printf -lftprintf -o $(MANDA)
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
	make clean -C ft_printf
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	make fclean -C ft_printf
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
