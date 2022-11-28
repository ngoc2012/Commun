# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2022/11/27 14:05:33 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = Libft/ft_memcmp.c Libft/ft_memcpy.c Libft/ft_calloc.c Libft/ft_putendl_fd.c Libft/ft_strnstr.c Libft/ft_isalpha.c Libft/ft_strtrim.c Libft/ft_memmove.c Libft/ft_isalnum.c Libft/ft_isdigit.c Libft/ft_isprint.c Libft/ft_tolower.c Libft/ft_toupper.c Libft/ft_strncmp.c Libft/ft_strlen.c Libft/ft_putstr_fd.c Libft/ft_bzero.c Libft/ft_memset.c Libft/ft_substr.c Libft/ft_strmapi.c Libft/ft_strchr.c Libft/ft_atoi.c Libft/ft_isascii.c Libft/ft_itoa.c Libft/ft_putchar_fd.c Libft/ft_strjoin.c Libft/ft_split.c Libft/ft_strlcat.c Libft/ft_putnbr_fd.c Libft/ft_memchr.c Libft/ft_strrchr.c Libft/ft_striteri.c Libft/ft_strdup.c Libft/ft_strlcpy.c Libft/ft_lstdelone.c Libft/ft_lstadd_front.c Libft/ft_lstclear.c Libft/ft_lstadd_back.c Libft/ft_lstnew.c Libft/ft_lstsize.c Libft/ft_lstiter.c Libft/ft_lstmap.c Libft/ft_lstlast.c
LIBS = ft_printf.c ft_get_elements.c ft_get_types.c ft_itoa_base.c ft_usitoa.c ft_get_cspu.c ft_content.c ft_print_out.c
BONS = ft_printf.c ft_get_elements.c ft_get_types.c ft_itoa_base.c ft_usitoa.c ft_get_cspu.c ft_content.c ft_print_out.c
OBJS = ${LIBFT:.c=.o} ${LIBS:.c=.o}
BONO = ${BONS:.c=.o}
LIBN = libftprintf.a 
all: $(LIBN)
.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o} -I.
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
