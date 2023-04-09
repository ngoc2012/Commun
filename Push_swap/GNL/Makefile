# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/03/07 17:08:55 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNLS = get_next_line_bonus.c get_next_line_utils_bonus.c
GNLO = ${GNLS:.c=.o}
GNLN = libftgnl.a 
all: $(GNLN)
.c.o:
	cc -Wall -Wextra -Werror -g -c $< -o ${<:.c=.o} -I.
$(GNLN): $(GNLO)
	ar rc $(GNLN) $(GNLO)
clean:
	rm -f $(GNLO)
fclean: clean
	rm -f $(GNLN)
re: fclean all
.PHONY:	all clean fclean re
