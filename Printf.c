#include <stdio.h>
#include "Printf/libftprintf.h"

int	main()
{

	//cspdiuxX%
	//
	// c : int -> unsigned char
	printf ("%%c : int -> unsigned char. Characters: 'z': %c, 122: %c \n", 'z', 122);
	// s : const char *
	printf ("%%s : const char *. Exemple:  %s \n", "Educative");
	// p : The void * pointer argument is printed in
	// hexadecimal  (as if by %#x or %#lx).
	unsigned int	a = 10;
	printf("%%p : The void * pointer argument is printed in\n \
	hexadecimal  (as if by %%#x or %%#lx). %p %#x %#lx\n", &a, (unsigned int) &a, (long) &a);
	// d,i : The int argument is converted to signed decimal  notation
	//
	// u,x,X : The  unsigned  int argument is converted to unsigned octal
        //      (o), unsigned decimal (u), or unsigned hexadecimal (x  and
        //      X)  notation.
	printf("%%u: Unsigned int -> unsigned decimal: %d: %u\n", 2000, 2000);
	printf("%%x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %x\n", 2000, 2000);
	printf("%%X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %X\n", 2000, 2000);
	printf("%%u: Unsigned int -> unsigned decimal: %d: %u\n", -2000, -2000);
	printf("%%x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %x\n", -2000, -2000);
	printf("%%X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %X\n", -2000, -2000);
	printf("Just print the percentage sign %%\n");
	//Manage any combination of the following flags: ’-0.’
	// and the field minimum width under all conversions.
	//
	// Manage all the following flags: ’# +’
	//printf ("Integers: %i %u \n", -3456, 3456);
	ft_printf ("Integers: %i %u \n", -3456, 3456);
	
	//printf( "%+09d\n", 452 );
	//printf( "%09d\n", 452 );
	//printf( "%09d\n", 0 );
	//printf( "% 9d\n", 452 );
	//printf( "%-09d\n", 452 );
	//printf( "%.09d\n", 452 );
	//printf( "%-.9d\n", 452 );
	//printf( "%-0.9d\n", 452 );
	/*
	printf ("Integers: %i %u \n", -3456, 3456);
	printf ("Decimals: %d %ld\n", 1997, 32000L);
	printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
	printf ("floats: %4.2f %+.0e %E \n", 3.14159, 3.14159, 3.14159);
	printf ("Preceding with empty spaces: %10d \n", 1997);
	printf ("Preceding with zeros: %010d \n", 1997);
	printf ("Width: %*d \n", 15, 140);
	printf ("%s \n", "Educative");

	int a,b;
	float c,d;

	a = 15;
	b = a / 2;
	printf("%d\n",b);
	printf("%3d\n",b);
	printf("%03d\n",b);

	c = 15.3;
	d = c / 3;
	printf("%3.2f\n",d);

	for (int Fahrenheit = 0; Fahrenheit <= 300; Fahrenheit = Fahrenheit + 20)
		printf("%3d %06.3f\n", Fahrenheit, (5.0/9.0)*(Fahrenheit-32));

	printf("The color: %s\n", "blue");
	printf("First number: %d\n", 12345);
	printf("Second number: %04d\n", 25);
	printf("Third number: %i\n", 1234);
	printf("Float number: %3.2f\n", 3.14159);
	printf("Hexadecimal: %x\n", 255);
	printf("Octal: %o\n", 255);
	printf("Unsigned value: %u\n", 150);


	printf(":%s:\n", "Hello, world!");
	printf(":%15s:\n", "Hello, world!");
	printf(":%.10s:\n", "Hello, world!");
	printf(":%-10s:\n", "Hello, world!");
	printf(":%-15s:\n", "Hello, world!");
	printf(":%.15s:\n", "Hello, world!");
	printf(":%15.10s:\n", "Hello, world!");
	printf(":%-15.10s:\n", "Hello, world!");
*/
}
