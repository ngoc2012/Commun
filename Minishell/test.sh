#make && valgrind --leak-check=full --show-leak-kinds=all ./minishell
#make && valgrind --leak-check=full ./minishell
make && valgrind --suppressions=rl.supp --leak-check=full --track-fds=yes --show-leak-kinds=all ./minishell
#make && valgrind --tool=helgrind --suppressions=rl.supp --track-fds=yes ./minishell
