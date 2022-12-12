# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/10 14:40:03 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
all: $(FILE)
bonus:
	$(CC) $(CFLAGS) *.c -L. -lftprintf -o $(FILE)
$(FILE):
	$(CC) $(CFLAGS) *.c *.h -L. -lftprintf -I. -o $(FILE)
clean:
	rm -f *.o
fclean: clean
	rm -f $(FILE)
re: fclean all
