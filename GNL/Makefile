# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/05 10:48:03 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = ft_printf.c ft_printf/ft_elmt_type.c ft_printf/ft_prtf_type.c ft_printf/ft_usitoa.c ft_printf/ft_itoa_base.c
BONS = ft_printf.c ft_printf/ft_elmt_type.c ft_printf/ft_prtf_type.c ft_printf/ft_usitoa.c ft_printf/ft_itoa_base.c
OBJS = ${LIBFT:.c=.o} ${LIBS:.c=.o}
BONO = ${BONS:.c=.o}
LIBN = libftprintf.a 
all: $(LIBN)
.c.o:
	cc -Wall -Wextra -Werror -g -c $< -o ${<:.c=.o} -I.
bonus: $(BONO)
	ar rc $(LIBN) $(BONO) $(OBJS)
$(LIBN): $(OBJS)
	ar rc $(LIBN) $(OBJS)
clean:
	rm -f $(OBJS)
	rm -f $(BONO)
fclean: clean
	rm -f $(LIBN)
re: fclean all
