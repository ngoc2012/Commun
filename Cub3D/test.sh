clear && make re && make clean && valgrind --leak-check=full --show-leak-kinds=all ./cub3D
#make && valgrind --leak-check=full ./minishell
#make && valgrind --suppressions=rl.supp --leak-check=full --track-fds=yes --show-leak-kinds=all ./minishell
#make && valgrind --tool=helgrind --suppressions=rl.supp --track-fds=yes ./minishell

#echo "echo test tout;echo $?; exit" | ./minishell
#echo "echo test tout;echo $?; exit" | bash
#TEST2=$(echo "echo test tout; exit" | bash 2>&-)
#echo "$TEST2"

