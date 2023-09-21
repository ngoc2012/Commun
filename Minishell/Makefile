# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/21 16:13:24 by minh-ngu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c prompt.c minishell.c priorities_operators.c infix_priorities_operators.c remove_quotes.c pipe.c split_args.c args_list.c args_list_wild.c strjoinm.c ft_split_quote.c ft_strcmp_val.c wildcards.c wild_files_list.c command.c process.c heredoc.c heredoc_signal.c redir_in.c redir_out.c error.c ft_array_str.c builtins/echo.c builtins/dir.c builtins/env.c builtins/export.c builtins/export_all.c builtins/builtin.c builtins/get_env.c builtins/get_str_env.c builtins/ft_strdcmp.c builtins/chr_pos.c builtins/exit.c builtins/abs_path.c builtins/set_pipe.c get_next_line.c get_next_line_utils.c
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBS = libft
all:	$(MANDA)
$(LIBFT):
	make -C libft
.c.o:
	$(CC) $(FLAGS) -g -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):	$(MOBJ) $(LIBFT)
	$(CC) $(FLAGS) $(MOBJ) -lncurses -lreadline -L./libft -lft -o $(MANDA)
bonus:	$(MANDA)
norm:
	norminette $(LIBS) srcs includes
gits:
	make fclean
	git add Makefile
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.c, $(LIBS))
	git add $(addprefix srcs/, $(SRCS))
	git add $(addsuffix /*.h, $(LIBS) includes)
	git commit -m "all"
	git push origin
clean:
	make clean -C libft
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
