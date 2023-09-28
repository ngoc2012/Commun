# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/28 15:50:30 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXOS1 = ex00 ex01 ex03 ex05 ex06
EXOS = ex00 ex01 ex02 ex03 ex04 ex05 ex06
gits:
	git add $(addsuffix /Makefile, $(EXOS))
	git add $(addsuffix /*.cpp, $(EXOS))
	git add $(addsuffix /*.hpp, $(EXOS1))
	git commit -m "all"
	git push
.PHONY: all clean fclean re
