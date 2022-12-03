cd libft-war-machine
bash grademe.sh
cd ..
cd libftTester
make fclean && rm ../*.so
make
cd ..
cd libft-unit-test
make fclean && rm ../*.so
make
cd ..
