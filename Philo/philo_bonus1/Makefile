# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/04/18 15:41:27 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c philo.c time.c sem.c
OBJS = ${SRCS:.c=.o}
FILE = philo_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
all:	$(FILE)
.c.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.c=.o} -I./
$(FILE):	$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(FILE)
norm:
	norminette *.c *.h
git:
	cd ..
	git add philo/Makefile philo/*.c philo/*.h
	git add philo_bonus/Makefile philo_bonus/*.c philo_bonus/*.h
	git commit -m "all"
	git push
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(FILE)
re: fclean all
.PHONY: all clean fclean re
