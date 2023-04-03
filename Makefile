# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/12/17 07:29:54 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY = get_next_line.c get_next_line_utils.c
BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

fclean:
	rm -f a.out
#GNL: fclean
#	cc -Wall -g $@.c $(addprefix $@/, $(MANDATORY)) -I./$@
#	valgrind -s --leak-check=full ./a.out
#	./a.out
#	cc -Wall -g $@.c $(addprefix $@/, $(MANDATORY)) -I./$@ -D BUFFER_SIZE=1
#	valgrind -s --leak-check=full ./a.out
#	./a.out
GNL: fclean
	cc -Wall -g $@.c $(addprefix $@/, $(BONUS)) -I./$@ -D BUFFER_SIZE=10000000
	valgrind -s --max-stackframe=10000256 --leak-check=full ./a.out
	./a.out
Printf: fclean
	cc -Wall -g $@.c $@/*.c $@/libft/*.c -I./$@
	valgrind -s --leak-check=full ./a.out
	./a.out
#Printf: fclean
#	cc -Wall -g $@.c -L./$@ -lftprintf -I./$@
#	valgrind -s --leak-check=full ./a.out
#	./a.out
Libft: fclean
	cc -Wall -g $@.c $@/*.c Libs/*.c -I./$@ -lbsd
	valgrind -s --leak-check=full ./a.out
	./a.out
#Libft: fclean
#	cc -Wall -g $@.c -L./$@ -lft -lft1 -I./$@ -lbsd
#	valgrind -s --leak-check=full ./a.out
#	./a.out
