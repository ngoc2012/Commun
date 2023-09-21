#make re && valgrind --suppressions=rl.supp --leak-check=full --show-leak-kinds=all ./minishell
#make re && valgrind --leak-check=full --show-leak-kinds=all ./minishell
#make && valgrind --leak-check=full ./minishell
#make re && valgrind --suppressions=rl.supp --leak-check=full --track-fds=yes --show-leak-kinds=all ./minishell
#make re && make clean && valgrind --trace-children=yes --suppressions=rl.supp --leak-check=full --track-fds=yes --show-leak-kinds=all ./minishell
make re && make clean && valgrind --trace-children=yes --suppressions=rl.supp --leak-check=full --track-fds=yes --show-leak-kinds=all env -i ./minishell
#make re && make clean && valgrind --trace-children=yes --track-fds=yes env -i ./minishell
#make && valgrind --tool=helgrind --suppressions=rl.supp --track-fds=yes ./minishell

#echo "echo test tout;echo $?; exit" | ./minishell
#echo "echo test tout;echo $?; exit" | bash
#TEST2=$(echo "echo test tout; exit" | bash 2>&-)
#echo "$TEST2"

