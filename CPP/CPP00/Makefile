# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/27 05:32:16 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FOLDERS = ex00 ex01
gits:
	git add Makefile
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.cpp, $(LIBS))
	git add $(addsuffix /*.hpp, $(LIBS))
	git add ex02/Account.cpp
	git commit -m "all"
	git push
.PHONY: all clean fclean re
