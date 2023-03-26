#make && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fract-ol Julia
make && valgrind --leak-check=full ./fract-ol Mandelbrot
