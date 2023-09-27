# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/27 05:38:43 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXOS = ex00 ex01
gits:
	git add Makefile
	git add $(addsuffix /Makefile, $(EXOS))
	git add $(addsuffix /*.cpp, $(EXOS))
	git add $(addsuffix /*.hpp, $(EXOS))
	git add ex02/Account.cpp
	git commit -m "all"
	git push
.PHONY: all clean fclean re
