# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/11/19 05:55:20 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = ft_memcmp.c ft_memcpy.c ft_calloc.c ft_putendl_fd.c ft_strnstr.c ft_isalpha.c ft_strtrim.c ft_memmove.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_strlen.c ft_putstr_fd.c ft_bzero.c ft_memset.c ft_substr.c ft_strmapi.c ft_strchr.c ft_atoi.c ft_isascii.c ft_itoa.c ft_putchar_fd.c ft_strjoin.c ft_split.c ft_strlcat.c ft_putnbr_fd.c ft_memchr.c ft_strrchr.c ft_striteri.c ft_strdup.c ft_strlcpy.c
BONS = ft_lstdelone.c ft_lstadd_front.c ft_lstclear.c ft_lstadd_back.c ft_lstnew.c ft_lstsize.c ft_lstiter.c ft_lstmap.c ft_lstlast.c
OBJS = ${LIBS:.c=.o}
BONO = ${BONS:.c=.o}
LIBN = libft.a 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
all: $(LIBN)
so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(LIBS) $(BONS)
	$(CC) -nostartfiles -shared -o libft.so $(OBJS) $(BONO)
.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} -I.
bonus: $(BONO) $(OBJS)
	ar rc $(LIBN) $(BONO) $(OBJS)
$(LIBN): $(OBJS)
	ar rc $(LIBN) $(OBJS)
clean:
	rm -f $(BONO) $(OBJS)
fclean: clean
	rm -f $(LIBN)
re: fclean all
