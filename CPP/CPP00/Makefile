# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/28 13:44:46 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXOS1 = ex01 ex02
EXOS = ex00 ex01 ex02
gits:
	git add Makefile
	git add $(addsuffix /Makefile, $(EXOS))
	git add $(addsuffix /*.cpp, $(EXOS))
	git add $(addsuffix /*.hpp, $(EXOS1))
	git commit -m "all"
	git push
.PHONY: all clean fclean re
