# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/26 18:35:15 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = megaphone.cpp
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = megaphone
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all:	$(MANDA)
.c.o:
	$(CC) $(FLAGS) $(INCL_MINILIBX) -g -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):	$(MOBJ) $(LIBFT) $(LIBGNL) $(LIBML) 
	$(CC) $(FLAGS) $(MOBJ) $(OBJ_MINILIBX) -L./libft -lft -L./GNL -lgnl -o $(MANDA)
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
	make clean -C GNL
	make clean -C minilibx-linux
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	make fclean -C GNL	
	make clean -C minilibx-linux
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
