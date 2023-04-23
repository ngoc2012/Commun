#pgrep philo_bonus | xargs kill
#./philo_bonus 4 310 200 100 5
#./philo_bonus 5 8 2 2 5
#./philo_bonus 5 4 1 1 10
#./philo_bonus 5 800 200 200 5
#./philo_bonus 4 410 200 200 5
#./philo_bonus 1 410 200 200 5
#./philo_bonus 1 11 5 5
#valgrind --tool=helgrind ./philo_bonus 5 800 200 200 5
#valgrind --leak-check=full ./philo_bonus 5 800 200 200 5
#valgrind --tool=helgrind ./philo_bonus 4 410 200 200 5
#valgrind --leak-check=full ./philo_bonus 4 410 200 200 5
#valgrind --tool=helgrind ./philo_bonus 4 310 200 100 5
#valgrind --leak-check=full ./philo_bonus 4 310 200 100 5
#valgrind --tool=helgrind ./philo_bonus 1 11 5 5
#valgrind --leak-check=full ./philo_bonus 1 11 5 5
#./philo 4 310 200 100
#echo "========================"
#../philo/philo 4 310 200 100 5
#./philo 5 8 2 2
#./philo 5 3 1 1 10
#./philo 5 800 200 200 5
#./philo 4 410 200 200 5
#./philo 1 410 200 200
#./philo 1 11 5 5
#valgrind --tool=helgrind ./philo 1 11 5 5
#valgrind --leak-check=full ./philo 1 11 5 5
valgrind --tool=helgrind ./philo 5 800 200 200 5
valgrind --leak-check=full ./philo 5 800 200 200 10
#valgrind --tool=helgrind ./philo 4 310 200 100 10
#valgrind --leak-check=full ./philo 4 310 200 100 10
#valgrind --tool=helgrind ./philo 4 410 200 200 5
#valgrind --leak-check=full ./philo 4 410 200 200 5
