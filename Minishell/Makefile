# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/08/31 16:26:17 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c minishell.c priorities_operators.c infix_priorities_operators.c remove_quotes.c pipe.c split_args.c args_list.c strjoinm.c ft_split_quote.c ft_strcmp_val.c wildcards.c wild_files_list.c command.c process.c heredoc.c heredoc_signal.c redir_in.c redir_out.c error.c builtins/echo.c builtins/dir.c builtins/env.c builtins/export.c builtins/export_all.c builtins/builtin.c builtins/get_env.c builtins/ft_strdcmp.c builtins/chr_pos.c builtins/exit.c builtins/abs_path.c
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = minishell
CC = cc
#FLAGS = -Wall -Wextra -Werror
FLAGS = -Wextra
LIBFT = libft/libft.a
LIBPR = ft_printf/libftprintf.a
LIBS = libft ft_printf
all:	$(MANDA)
$(LIBFT):
	make -C libft
$(LIBPR):
	make -C ft_printf
.c.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):	$(MOBJ) $(LIBFT) $(LIBPR)
	$(CC) $(FLAGS) $(MOBJ) -lncurses -lreadline -L./libft -lft -L./ft_printf -lftprintf -o $(MANDA)
bonus:	$(MANDA)
norm:
	norminette $(LIBS) srcs includes
gits:
	git add Makefile
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.c, $(LIBS) srcs)
	git add $(addsuffix /*.h, $(LIBS) includes)
	git commit -m "all"
	git push
clean:
	make clean -C libft
	make clean -C ft_printf
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	make fclean -C ft_printf
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
