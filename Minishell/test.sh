#make && valgrind --leak-check=full --show-leak-kinds=all ./minishell
#make && valgrind --leak-check=full ./minishell
make && valgrind --leak-check=full --track-fds=yes ./minishell
