# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/27 12:15:08 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = philo philo_bonus
gits:
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.c, $(LIBS))
	git add $(addsuffix /*.h, $(LIBS))
	git commit -m "all"
	git push
.PHONY: all clean fclean re
