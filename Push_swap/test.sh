echo valgrind --leak-check=full -q ./push_swap
valgrind --leak-check=full -q ./push_swap
echo valgrind --leak-check=full -q ./push_swap 0
valgrind --leak-check=full -q ./push_swap 0
echo valgrind --leak-check=full -q ./push_swap 0 1
valgrind --leak-check=full -q ./push_swap 0 1
echo valgrind --leak-check=full -q ./push_swap 0 1 2 3 4 5 6 7 8 9
valgrind --leak-check=full -q ./push_swap 0 1 2 3 4 5 6 7 8 9
echo valgrind --leak-check=full -q ./push_swap \"0 1 2 3 4 5 6 7 8 9\"
valgrind --leak-check=full -q ./push_swap "0 1 2 3 4 5 6 7 8 9"
echo valgrind --leak-check=full -q ./push_swap \"0 1 2 3 4 \" 5 6 7 8 9
valgrind --leak-check=full -q ./push_swap "0 1 2 3 4 " 5 6 7 8 9
echo valgrind --leak-check=full -q ./push_swap 0 1 2 \"3 4 5 6\" 7 8 9
valgrind --leak-check=full -q ./push_swap 0 1 2 "3 4 5 6" 7 8 9
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
echo valgrind --leak-check=full -q ./push_swap \"-100 1\" \"2 3 4 5 00+6\" \"1000000\"
valgrind --leak-check=full -q ./push_swap "-100 1" "2 3 4 5 00+6" "1000000"
echo valgrind --leak-check=full -q ./push_swap \"00-100 1\" \"2 3 4 5 006\" \"1000000\"
valgrind --leak-check=full -q ./push_swap "00-100 1" "2 3 4 5 006" "1000000"
echo valgrind --leak-check=full -q ./push_swap \"-0000100 1\" \"2 3 4 5 006\" \"1000000\"
valgrind --leak-check=full -q ./push_swap "-0000100 1" "2 3 4 5 006" "1000000"
echo valgrind --leak-check=full -q ./push_swap \"-100 1\" \"2 3 4 5 +006\" \"10000000000\"
valgrind --leak-check=full -q ./push_swap "-100 1" "2 3 4 5 +006" "10000000000"
echo valgrind --leak-check=full -q ./push_swap \"-100 1\" \"2 3 4 5 +006\" \"1000000\" one 
valgrind --leak-check=full -q ./push_swap "-100 1" "2 3 4 5 +006" "1000000" one 


echo ARG="4 67 3 87 23"\; valgrind --leak-check=full -q ./push_swap \$ARG \| wc -l
ARG="4 67 3 87 23"; valgrind --leak-check=full -q ./push_swap $ARG | wc -l


wget https://projects.intra.42.fr/uploads/document/document/13274/checker_linux
chmod 777 checker_linux


echo valgrind --leak-check=full -q ./checker \"\" 1 
valgrind --leak-check=full -q ./checker "" 1 
echo valgrind --leak-check=full -q ./checker_linux \"\" 1 
valgrind --leak-check=full -q ./checker_linux "" 1 

echo valgrind --leak-check=full -q ./checker 3 2 one 0
valgrind --leak-check=full -q ./checker 3 2 one 0
echo valgrind --leak-check=full -q ./checker_linux 3 2 one 0
valgrind --leak-check=full -q ./checker_linux 3 2 one 0

echo ARG=\"\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker \$ARG
ARG=""; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker $ARG
echo ARG=\"\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker_linux \$ARG
ARG=""; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker_linux $ARG

echo ARG=\"4\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker \$ARG
ARG="4"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker $ARG
echo ARG=\"4\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker_linux \$ARG
ARG="4"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker_linux $ARG

echo ARG=\"4 67\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker \$ARG
ARG="4 67"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker $ARG
echo ARG=\"4 67\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker_linux \$ARG
ARG="4 67"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker_linux $ARG

echo ARG=\"4 67 3 87 23\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker \$ARG
ARG="4 67 3 87 23"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker $ARG
echo ARG=\"4 67 3 87 23\"\; valgrind --leak-check=full -q ./push_swap \$ARG \| valgrind --leak-check=full -q ./checker_linux \$ARG
ARG="4 67 3 87 23"; valgrind --leak-check=full -q ./push_swap $ARG | valgrind --leak-check=full -q ./checker_linux $ARG
