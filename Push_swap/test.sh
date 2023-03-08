echo valgrind --leak-check=full -q ./push_swap
valgrind --leak-check=full -q ./push_swap
echo valgrind --leak-check=full -q ./push_swap 0
valgrind --leak-check=full -q ./push_swap 0
echo valgrind --leak-check=full -q ./push_swap 0 1
valgrind --leak-check=full -q ./push_swap 0 1
echo valgrind --leak-check=full -q ./push_swap 0 1 2 3 4 5 6 7 8 9
valgrind --leak-check=full -q ./push_swap 0 1 2 3 4 5 6 7 8 9
echo valgrind --leak-check=full -q ./push_swap 0 1 2 3 4 \"5 6 7 8 9\"
valgrind --leak-check=full -q ./push_swap 0 1 2 3 4 "5 6 7 8 9"
echo valgrind --leak-check=full -q ./push_swap 0 one 2 3
valgrind --leak-check=full -q ./push_swap 0 one 2 3
echo valgrind --leak-check=full -q ./push_swap 0 one 2 +3
valgrind --leak-check=full -q ./push_swap 0 one 2 +3
echo valgrind --leak-check=full -q ./push_swap 00000 1 2 +3
valgrind --leak-check=full -q ./push_swap 00000 1 2 +3
echo valgrind --leak-check=full -q ./push_swap 00000 0001 2 +3
valgrind --leak-check=full -q ./push_swap 00000 0001 2 +3
echo valgrind --leak-check=full -q ./push_swap \"-100 1\" \"2 3 4 5 +006\" \"1000000\"
valgrind --leak-check=full -q ./push_swap "-100 1" "2 3 4 5 +006" "1000000"
echo valgrind --leak-check=full -q ./push_swap \"-100 1\" \"2 3 4 5 +006\" \"100000000\"
valgrind --leak-check=full -q ./push_swap "-100 1" "2 3 4 5 +006" "100000000"
echo valgrind --leak-check=full -q ./push_swap \"-100 1\" \"2 3 4 5 +006\" \"1000000\" one 
valgrind --leak-check=full -q ./push_swap "-100 1" "2 3 4 5 +006" "1000000" one 

echo valgrind --leak-check=full -q ./checker \"\" 1 
valgrind --leak-check=full -q ./checker "" 1 
echo valgrind --leak-check=full -q ./checker 3 2 one 0
valgrind --leak-check=full -q ./checker 3 2 one 0

echo ARG="4 67 3 87 23"\; valgrind --leak-check=full -q ./push_swap \$ARG \| wc -l
ARG="4 67 3 87 23"; valgrind --leak-check=full -q ./push_swap $ARG | wc -l
echo ARG="4 67 3 87 23"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker \$ARG
ARG="4 67 3 87 23"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker $ARG


wget https://projects.intra.42.fr/uploads/document/document/13274/checker_linux
chmod 777 checker_linux
echo ARG=\"4 67 3 87 23\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker_linux \$ARG
ARG="4 67 3 87 23"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker_linux $ARG
