# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/11/11 08:45:06 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = ft_print_memory.c ft_free_strs.c 
SRCS = test.c
OBJS = ${LIBS:.c=.o}
LIBN = libft1.a 
all: $(LIBN)
.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o} -I.
$(LIBN): $(OBJS)
	ar rc $(LIBN) $(OBJS)
	rm -f $(OBJS)
	cp $(LIBN) ../Libft/$(LIBN)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(LIBN)
re: fclean all
test:
	gcc -Wall -g $(SRCS) -L. -lft -I.
testexe:
	gcc -Wall -g $(SRCS) -L. -lft -I.
	./a.out
final:
	gcc -Wall -Wextra -Werror $(SRCS) -L. -lft -I.
	./a.out
