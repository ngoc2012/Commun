# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/11/09 10:58:13 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

fclean:
	rm -f a.out
Libft: fclean
	gcc -Wall -g $@.c -L./$@ -lft -lft1 -I./$@ -lbsd
	valgrind --leak-check=full ./a.out
	./a.out
