# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/11/17 16:12:44 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

fclean:
	rm -f a.out
Printf: fclean
	gcc -Wall -g $@.c $@/*.c $@/Libft/*.c -I./$@
	valgrind -s --leak-check=full ./a.out
	./a.out
#Printf: fclean
#	gcc -Wall -g $@.c -L./$@ -lftprintf -I./$@
#	valgrind -s --leak-check=full ./a.out
#	./a.out
Libft: fclean
	gcc -Wall -g $@.c $@/*.c -I./$@
	valgrind -s --leak-check=full ./a.out
	./a.out
#Libft: fclean
#	gcc -Wall -g $@.c -L./$@ -lft -lft1 -I./$@ -lbsd
#	valgrind -s --leak-check=full ./a.out
#	./a.out
