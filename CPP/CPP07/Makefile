# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2024/02/15 10:23:57 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXOS = ex00 ex01 ex02
gits:
	git add $(wildcard $(addsuffix /Makefile, $(EXOS)))
	git add $(wildcard $(addsuffix /*.cpp, $(EXOS)))
	git add $(wildcard $(addsuffix /*.tpp, $(EXOS)))
	git add $(wildcard $(addsuffix /*.hpp, $(EXOS)))
	git commit -m "all"
	git push
.PHONY: all clean fclean re
