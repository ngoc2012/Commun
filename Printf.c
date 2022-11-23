#include <stdio.h>
#include "Printf/libftprintf.h"

int	main()
{
/*
	//cspdiuxX%
	printf("================= cispdiuxX%% =================\n");
	ft_printf("================= cispdiuxX%% =================\n");
	//
	// c : int -> unsigned char
	printf ("%%c : int -> unsigned char. Characters: 'z': %c, 122: %c \n", 'z', 122);
	ft_printf ("%%c : int -> unsigned char. Characters: 'z': %c, 122: %c \n", 'z', 122);
	// s : const char *
	printf ("%%s : const char *. Exemple:  %s sdhfiofdsi\n", "Educative");
	ft_printf ("%%s : const char *. Exemple:  %s sdhfiofdsi\n", "Educative");
	// p : The void * pointer argument is printed in
	// hexadecimal  (as if by %#x or %#lx).
	unsigned int	a = 10;
	printf("%%p : The void * pointer argument is printed in\n \
	hexadecimal  (as if by %%#x or %%#lx). %p %#x\n", &a, &a);
	ft_printf("%%p : The void * pointer argument is printed in\n \
	hexadecimal  (as if by %%#x or %%#lx). %p %#x\n", &a, &a);
	// d,i : The int argument is converted to signed decimal  notation
	//
	// u,x,X : The  unsigned  int argument is converted to unsigned octal
        //      (o), unsigned decimal (u), or unsigned hexadecimal (x  and
        //      X)  notation.

	
	printf("%%u: Unsigned int -> unsigned decimal: %d: %u\n", 4242, 4242);
	ft_printf("%%u: Unsigned int -> unsigned decimal: %d: %u\n", 4242, 4242);
	printf("%%x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %x\n", 4242, 4242);
	ft_printf("%%x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %x\n", 4242, 4242);
	printf("%%X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %X\n", 4242, 4242);
	ft_printf("%%X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %X\n", 4242, 4242);
	printf("%%u: Unsigned int -> unsigned decimal: %d: %u\n", -4242, -4242);
	ft_printf("%%u: Unsigned int -> unsigned decimal: %d: %u\n", -4242, -4242);
	printf("%%x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %x\n", -4242, -4242);
	ft_printf("%%x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %x\n", -4242, -4242);
	printf("%%X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %X\n", -4242, -4242);
	ft_printf("%%X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %X\n", -4242, -4242);

	printf("Just print the percentage sign %% \n");
	ft_printf("Just print the percentage sign %% \n");
	printf("Just print the percentage sign %  %jyyyy\n");
	ft_printf("Just print the percentage sign %  %jyyyy\n");
	printf("Just print the percentage sign % +-%jyrw\n");
	ft_printf("Just print the percentage sign % +-%jyrw\n");
	printf("Just print the percentage sign %%i \n", 10);
	ft_printf("Just print the percentage sign %%i \n", 10);
	printf("Just print the percentage sign %  %i \n", 10);
	ft_printf("Just print the percentage sign %  %i \n", 10);
	

	printf("================= BONUS =================\n");
	printf("The character %% is followed by zero or more of the following flags\n");
	//Manage any combination of the following flags: ’-0.’
	// and the field minimum width under all conversions.
	//
	printf("0      The value should be zero padded\n");
	printf("% 109d\n", 4242);
	ft_printf("% 109d\n", 4242);
	printf("%000109d\n", 4242);
	ft_printf("%000109d\n", 4242);
	printf("%09d\n", 0);
	ft_printf("%09d\n", 0);
	printf("%0 9d\n", 0);
	ft_printf("%0 9d\n", 0);
	printf("% 09d\n", 0);
	ft_printf("% 09d\n", 0);

	//printf("%-.# +09d\n", 0);
	//ft_printf("%-.# +09d\n", 0);
	printf("-      The  converted  value  is  to  be left adjusted on the field boundary\n");
	printf("#%- 9d#\n", 4242 );
	ft_printf("#%- 9d#\n", 4242 );
	printf("#%-09d#\n", 4242 );
	ft_printf("#%-09d#\n", 4242 );
	printf("A -  overrides  a  0  if  both  are given\n");
	// Manage all the following flags: ’# +’
	printf("Manage all the following flags: ’# +’\n");
	printf("%%#x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %#x\n", 4242, 4242);
	printf("%%#X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %#X\n", 4242, 4242);
	printf("%%#x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %#x\n", 0, 0);
	printf("%%#X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %#X\n", 0, 0);
	printf("' '    (a space) A blank should be left before a positive number (or empty string) produced by a signed conversion\n");
	printf("#% 9d#\n", 4242 );
	printf("+      A  sign  (+  or -) should always be placed before a number produced by a signed conversion.  By default, a sign is used only for negative numbers.\n");
	printf("A + overrides a space if both are used.\n");

	// s : const char *
	printf("================= ERRORS =================\n");
	printf("unknown conversion type character ‘...’ in format\n");
	printf("%%#c : '#' flag used with ‘%%c’ gnu_printf format\n");
	printf("%%#s : '#' flag used with ‘%%s’ gnu_printf format\n");
	printf("%%#p : '#' flag used with ‘%%p’ gnu_printf format\n");
	printf("%%##x: repeated '#' flag in format\n");
	printf("%%009d : repeated '0' flag in format\n");
	printf("%% c : ' ' flag used with ‘%%c’ gnu_printf format\n");
	//printf ("Integers: %i %u \n", -3456, 3456);


	//printf ("Integers: %+019i jsadlfd %+u oiodfsi %#0  -%  \n", -3456, 3456);
	//ft_printf ("Integers: %+019i jsadlfd %+u oiodfsi %#0  -%  \n", -3456, 3456);
	
	printf( "%+09d\n", 452 );
	ft_printf( "%+09d\n", 452 );
	printf( "#%-09d#\n", 452 );
	ft_printf( "#%-09d#\n", 452 );
	printf( "%.09d\n", 452 );
	ft_printf( "%.09d\n", 452 );
	printf( "%-.9d\n", 452 );
	ft_printf( "%-.9d\n", 452 );
	printf( "%-0.9d\n", 452 );
	ft_printf( "%-0.9d\n", 452 );
	printf( "%.-09d\n", 452 );
	ft_printf( "%.-09d\n", 452 );
	
	
	printf ("Integers: %i %u \n", -3456, 3456);
	ft_printf ("Integers: %i %u \n", -3456, 3456);
	printf ("Preceding with empty spaces: %10d \n", 1997);
	ft_printf ("Preceding with empty spaces: %10d \n", 1997);
	printf ("Preceding with zeros: %010d \n", 1997);
	ft_printf ("Preceding with zeros: %010d \n", 1997);

	int a,b;
	float c,d;

	a = 15;
	b = a / 2;
	printf("%d\n",b);
	ft_printf("%d\n",b);
	printf("%3d\n",b);
	ft_printf("%3d\n",b);
	printf("%03d\n",b);
	ft_printf("%03d\n",b);

	printf("The color: %s\n", "blue");
	ft_printf("The color: %s\n", "blue");
	printf("First number: %d\n", 12345);
	ft_printf("First number: %d\n", 12345);
	printf("Second number: %04d\n", 25);
	ft_printf("Second number: %04d\n", 25);
	printf("Third number: %i\n", 1234);
	ft_printf("Third number: %i\n", 1234);
	printf("Hexadecimal: %x\n", 255);
	ft_printf("Hexadecimal: %x\n", 255);
	printf("Unsigned value: %u\n", 150);
	ft_printf("Unsigned value: %u\n", 150);


	printf(":%s:\n", "Hello, world!");
	ft_printf(":%s:\n", "Hello, world!");
	printf(":%5s:\n", "Hello, world!");
	ft_printf(":%5s:\n", "Hello, world!");
	printf(":%15s:\n", "Hello, world!");
	ft_printf(":%15s:\n", "Hello, world!");
*/	printf(":%.10s:\n", "Hello, world!");
	ft_printf(":%.10s:\n", "Hello, world!");
	printf(":%-10s:\n", "Hello, world!");
	ft_printf(":%-10s:\n", "Hello, world!");
	printf(":%-15s:\n", "Hello, world!");
	ft_printf(":%-15s:\n", "Hello, world!");
	printf(":%.15s:\n", "Hello, world!");
	ft_printf(":%.15s:\n", "Hello, world!");
	printf(":%15.10s:\n", "Hello, world!");
	ft_printf(":%15.10s:\n", "Hello, world!");
	printf(":%-15.10s:\n", "Hello, world!");
	ft_printf(":%-15.10s:\n", "Hello, world!");

}
