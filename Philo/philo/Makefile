# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/04/11 17:53:55 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c check.c mutex.c time.c philo.c
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = philo
SRCS1 = philo_bonus.c
BONUS = philo_bonus
BSRC = $(addprefix srcs/, $(SRCS1))
BOBJ = ${BSRC:.c=.o}
CC = cc
FLAGS = -Wall -Wextra -Werror
all:	$(MANDA)
.c.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.c=.o} $(addprefix -I./, includes)
$(MANDA):	$(MOBJ)
	$(CC) $(FLAGS) $(MOBJ) -o $(MANDA)
$(BONUS):	$(MOBJ)
	$(CC) $(FLAGS) $(MOBJ) -o $(BONUS)
norm:
	norminette srcs includes
git:
	git add Makefile
	git add $(addsuffix /*.c, srcs)
	git add $(addsuffix /*.h, includes)
	git commit -m "all"
	git push
clean:
	rm -f $(MOBJ)
fclean: clean
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
