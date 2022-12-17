# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/17 13:54:38 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTFOLDER = ../libft
MANS = ft_printf.c elmt_type.c prtf.c ft_usitoa.c ft_itoa_base.c ft_usitoa_base.c
MANO = ${MANS:.c=.o}
LIBPR = libftprintf.a 
CC = cc
FLAGS = -Wall -Wextra -Werror
all: $(LIBN)
.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o} -I. -I$(LIBFTFOLDER)
$(LIBPR): $(MANO)
	ar rc $(LIBPR) $(MANO)
clean:
	rm -f $(MANO)
fclean: clean
	rm -f $(LIBPR)
re: fclean all

