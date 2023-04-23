# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/04/22 20:02:49 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c init.c philo.c time.c sem.c thread.c end.c
OBJS = ${SRCS:.c=.o}
FILE = philo_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
all:	$(FILE)
.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o} -I./
$(FILE):	$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(FILE)
norm:
	norminette *.c *.h
git:
	cd ..
	git add Makefile *.h $(SRCS)
	git commit -m "all"
	git push
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(FILE)
re: fclean all
.PHONY: all clean fclean re
