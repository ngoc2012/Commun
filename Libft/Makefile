# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/11/11 08:29:11 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = ft_memcmp.c ft_memcpy.c ft_calloc.c ft_strnstr.c ft_isalpha.c ft_strtrim.c ft_memmove.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_strlen.c ft_bzero.c ft_memset.c ft_substr.c ft_strchr.c ft_atoi.c ft_isascii.c ft_strjoin.c ft_split.c ft_strlcat.c ft_memchr.c ft_strrchr.c ft_strdup.c ft_strlcpy.c
SRCS = test.c
OBJS = ${LIBS:.c=.o}
LIBN = libft.a 
all: $(LIBN)
.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o} -I.
$(LIBN): $(OBJS)
	ar rc $(LIBN) $(OBJS)
	rm -f $(OBJS)
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
