# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/10/07 17:22:34 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXOS = ex00 ex01 ex02 ex03
gits:
	git add $(addsuffix /Makefile, $(EXOS))
	git add $(addsuffix /*.cpp, $(EXOS))
	git add $(addsuffix /*.hpp, $(EXOS))
	git commit -m "all"
	git push
.PHONY: all clean fclean re
