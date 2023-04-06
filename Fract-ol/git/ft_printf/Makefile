# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/01/04 09:50:20 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = ft_memcmp.c ft_memcpy.c ft_calloc.c ft_putendl_fd.c ft_strnstr.c ft_isalpha.c ft_strtrim.c ft_memmove.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_strlen.c ft_putstr_fd.c ft_bzero.c ft_memset.c ft_substr.c ft_strmapi.c ft_strchr.c ft_atoi.c ft_isascii.c ft_itoa.c ft_putchar_fd.c ft_strjoin.c ft_split.c ft_strlcat.c ft_putnbr_fd.c ft_memchr.c ft_strrchr.c ft_striteri.c ft_strdup.c ft_strlcpy.c ft_lstdelone.c ft_lstadd_front.c ft_lstclear.c ft_lstadd_back.c ft_lstnew.c ft_lstsize.c ft_lstiter.c ft_lstmap.c ft_lstlast.c
OBJS = ${LIBS:.c=.o}
LIBFTFOLDER = ../libft/
MANS = ft_printf.c elmt_type.c prtf.c ft_usitoa.c ft_itoa_base.c ft_usitoa_base.c
MANO = ${MANS:.c=.o}
LIBFT = libft.a 
LIBPR = libftprintf.a 
LIBPR0 = libftprintf0.a 
CC = cc
FLAGS = -Wall -Wextra -Werror
all: $(LIBPR)
.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o} -I. -I$(LIBFTFOLDER)
$(LIBPR): $(MANO)
	make -C $(LIBFTFOLDER)
	ar rc  $(LIBPR) $(addprefix $(LIBFTFOLDER), $(OBJS)) $(MANO)
clean:
	make clean -C $(LIBFTFOLDER)
	rm -f $(MANO)
fclean: clean
	make fclean -C $(LIBFTFOLDER)
	rm -f $(LIBPR)
re: fclean all
.PHONY: clean fclean re all
