#include <limits.h>
#include <stdio.h>
#include "Printf/ft_printf.h"

int	main()
{
	char *s;
	static int	a;
	static unsigned int		mx_u = 235;
static char				mx_c = 'G';
static char			   *mx_s = "Hello, World!";
static int				mx_i = 42;
a = ft_printf( "  %s    %p    %X    %c    %i    %x  \n", mx_s, 4218944, mx_u, mx_c, mx_i, mx_u	);printf("%d\n", a);
/*
a = printf( "  %%    %i    %X    %p    %c    %s  \n", mx_i, mx_u, 4218944, mx_c, mx_s		);//printf("%d\n", a);
a = printf( "  %u    %%    %s    %c    %x    %X  \n", mx_u, mx_s, mx_c, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %i    %c    %x    %u    %%    %X  \n", mx_i, mx_c, mx_u, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %c    %X    %i    %%    %s    %p  \n", mx_c, mx_u, mx_i, mx_s, 4218944		);//printf("%d\n", a);
a = printf( "  %p    %x    %i    %c    %s    %u  \n", 4218944, mx_u, mx_i, mx_c, mx_s, mx_u	);//printf("%d\n", a);
a = printf( "  %i    %s    %%    %u    %c    %x  \n", mx_i, mx_s, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = printf( "  %X    %p    %s    %%    %u    %x  \n", mx_u, 4218944, mx_s, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %c    %%    %u    %i    %x    %X  \n", mx_c, mx_u, mx_i, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %i    %p    %X    %u    %s    %x  \n", mx_i, 4218944, mx_u, mx_u, mx_s, mx_u	);//printf("%d\n", a);
a = printf( "  %X    %c    %p    %x    %i    %u  \n", mx_u, mx_c, 4218944, mx_u, mx_i, mx_u	);//printf("%d\n", a);
a = printf( "  %%    %i    %u    %s    %c    %X  \n", mx_i, mx_u, mx_s, mx_c, mx_u		);//printf("%d\n", a);
a = printf( "  %u    %c    %x    %s    %X    %i  \n", mx_u, mx_c, mx_u, mx_s, mx_u, mx_i	);//printf("%d\n", a);
a = printf( "  %s    %p    %X    %c    %i    %x  \n", mx_s, 4218944, mx_u, mx_c, mx_i, mx_u	);//printf("%d\n", a);
a = printf( "  %u    %c    %X    %x    %p    %s  \n", mx_u, mx_c, mx_u, mx_u, 4218944, mx_s	);//printf("%d\n", a);
a = printf( "  %c    %%    %i    %X    %u    %x  \n", mx_c, mx_i, mx_u, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %s    %%    %x    %X    %c    %u  \n", mx_s, mx_u, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = printf( "  %x    %s    %X    %%    %p    %i  \n", mx_u, mx_s, mx_u, 4218944, mx_i		);//printf("%d\n", a);
a = printf( "  %%    %p    %i    %c    %x    %X  \n", 4218944, mx_i, mx_c, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %c    %s    %%    %u    %p    %x  \n", mx_c, mx_s, mx_u, 4218944, mx_u		);//printf("%d\n", a);
a = printf( "  %c    %i    %u    %s    %p    %x  \n", mx_c, mx_i, mx_u, mx_s, 4218944, mx_u	);//printf("%d\n", a);
a = printf( "  %X    %x    %s    %c    %i    %u  \n", mx_u, mx_u, mx_s, mx_c, mx_i, mx_u	);//printf("%d\n", a);
a = printf( "  %x    %c    %X    %p    %s    %p  \n", mx_u, mx_c, mx_u, 4218944, mx_s, 4218944	);//printf("%d\n", a);
a = printf( "  %X    %%    %i    %s    %p    %x  \n", mx_u, mx_i, mx_s, 4218944, mx_u		);//printf("%d\n", a);
a = printf( "  %i    %p    %x    %c    %X    %p  \n", mx_i, 4218944, mx_u, mx_c, mx_u, 4218944	);//printf("%d\n", a);
a = printf( "  %X    %c    %i    %u    %x    %p  \n", mx_u, mx_c, mx_i, mx_u, mx_u, 4218944	);//printf("%d\n", a);
a = printf( "  %i    %u    %c    %%    %X    %p  \n", mx_i, mx_u, mx_c, mx_u, 4218944		);//printf("%d\n", a);
a = printf( "  %s    %i    %c    %p    %x    %u  \n", mx_s, mx_i, mx_c, 4218944, mx_u, mx_u	);//printf("%d\n", a);
a = printf( "  %p    %%    %x    %X    %i    %c  \n", 4218944, mx_u, mx_u, mx_i, mx_c		);//printf("%d\n", a);
a = printf( "  %X    %i    %s    %%    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, 4218944		);//printf("%d\n", a);
a = printf( "  %%    %u    %p    %i    %X    %c  \n", mx_u, 4218944, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = printf( "  %x    %X    %p    %s    %i    %c  \n", mx_u, mx_u, 4218944, mx_s, mx_i, mx_c	);//printf("%d\n", a);
a = printf( "  %c    %%    %s    %X    %x    %p  \n", mx_c, mx_s, mx_u, mx_u, 4218944		);//printf("%d\n", a);
a = printf( "  %x    %X    %p    %s    %i    %u  \n", mx_u, mx_u, 4218944, mx_s, mx_i, mx_u	);//printf("%d\n", a);
a = printf( "  %p    %u    %s    %X    %c    %p  \n", 4218944, mx_u, mx_s, mx_u, mx_c, 4218944	);//printf("%d\n", a);
a = printf( "  %X    %s    %x    %p    %%    %i  \n", mx_u, mx_s, mx_u, 4218944, mx_i		);//printf("%d\n", a);
a = printf( "  %x    %s    %%    %p    %i    %c  \n", mx_u, mx_s, 4218944, mx_i, mx_c		);//printf("%d\n", a);
a = printf( "  %s    %u    %x    %%    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c		);//printf("%d\n", a);
a = printf( "  %p    %i    %x    %%    %u    %X  \n", 4218944, mx_i, mx_u, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %%    %c    %X    %p    %u    %x  \n", mx_c, mx_u, 4218944, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %u    %c    %%    %p    %i    %s  \n", mx_u, mx_c, 4218944, mx_i, mx_s		);//printf("%d\n", a);
a = printf( "  %%    %i    %s    %u    %c    %X  \n", mx_i, mx_s, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = printf( "  %%    %i    %u    %s    %X    %p  \n", mx_i, mx_u, mx_s, mx_u, 4218944		);//printf("%d\n", a);
a = printf( "  %s    %c    %X    %%    %i    %p  \n", mx_s, mx_c, mx_u, mx_i, 4218944		);//printf("%d\n", a);
a = printf( "  %x    %X    %u    %i    %%    %s  \n", mx_u, mx_u, mx_u, mx_i, mx_s		);//printf("%d\n", a);
a = printf( "  %x    %u    %s    %i    %p    %p  \n", mx_u, mx_u, mx_s, mx_i, 4218944, 4218944	);//printf("%d\n", a);
a = printf( "  %X    %i    %s    %x    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, mx_u, 4218944	);//printf("%d\n", a);
a = printf( "  %c    %i    %%    %X    %p    %u  \n", mx_c, mx_i, mx_u, 4218944, mx_u		);//printf("%d\n", a);
a = printf( "  %s    %u    %i    %X    %%    %c  \n", mx_s, mx_u, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = printf( "  %%    %p    %X    %i    %s    %x  \n", 4218944, mx_u, mx_i, mx_s, mx_u		);//printf("%d\n", a);
a = printf( "  %i    %x    %p    %c    %u    %X  \n", mx_i, mx_u, 4218944, mx_c, mx_u, mx_u	);//printf("%d\n", a);
a = printf( "  %X    %c    %%    %i    %x    %s  \n", mx_u, mx_c, mx_i, mx_u, mx_s		);//printf("%d\n", a);
a = printf( "  %x    %c    %u    %X    %p    %p  \n", mx_u, mx_c, mx_u, mx_u, 4218944, 4218944	);//printf("%d\n", a);
a = printf( "  %p    %u    %c    %s    %i    %p  \n", 4218944, mx_u, mx_c, mx_s, mx_i, 4218944	);//printf("%d\n", a);
a = printf( "  %x    %p    %s    %u    %%    %c  \n", mx_u, 4218944, mx_s, mx_u, mx_c		);//printf("%d\n", a);
a = printf( "  %%    %i    %X    %p    %u    %s  \n", mx_i, mx_u, 4218944, mx_u, mx_s		);//printf("%d\n", a);
a = printf( "  %%    %u    %c    %s    %i    %x  \n", mx_u, mx_c, mx_s, mx_i, mx_u		);//printf("%d\n", a);
a = printf( "  %c    %i    %u    %x    %s    %p  \n", mx_c, mx_i, mx_u, mx_u, mx_s, 4218944	);//printf("%d\n", a);
a = printf( "  %c    %i    %s    %u    %x    %p  \n", mx_c, mx_i, mx_s, mx_u, mx_u, 4218944	);//printf("%d\n", a);
a = printf( "  %u    %%    %x    %i    %X    %c  \n", mx_u, mx_u, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = printf( "  %x    %s    %u    %i    %c    %X  \n", mx_u, mx_s, mx_u, mx_i, mx_c, mx_u	);//printf("%d\n", a);
a = printf( "  %%    %c    %i    %p    %s    %X  \n", mx_c, mx_i, 4218944, mx_s, mx_u		);//printf("%d\n", a);
a = printf( "  %s    %x    %%    %X    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c		);//printf("%d\n", a);
a = printf( "  %x    %X    %u    %c    %%    %i  \n", mx_u, mx_u, mx_u, mx_c, mx_i		);//printf("%d\n", a);
a = printf( "  %c    %%    %i    %p    %u    %X  \n", mx_c, mx_i, 4218944, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %i    %c    %%    %u    %X    %p  \n", mx_i, mx_c, mx_u, mx_u, 4218944		);//printf("%d\n", a);
a = printf( "  %s    %i    %x    %u    %c    %p  \n", mx_s, mx_i, mx_u, mx_u, mx_c, 4218944	);//printf("%d\n", a);
a = printf( "  %s    %x    %c    %p    %u    %X  \n", mx_s, mx_u, mx_c, 4218944, mx_u, mx_u	);//printf("%d\n", a);
a = printf( "  %%    %s    %p    %i    %X    %c  \n", mx_s, 4218944, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = printf( "  %x    %X    %i    %%    %s    %u  \n", mx_u, mx_u, mx_i, mx_s, mx_u		);//printf("%d\n", a);
a = printf( "  %s    %i    %X    %c    %%    %p  \n", mx_s, mx_i, mx_u, mx_c, 4218944		);//printf("%d\n", a);
a = printf( "  %x    %p    %c    %s    %X    %u  \n", mx_u, 4218944, mx_c, mx_s, mx_u, mx_u	);//printf("%d\n", a);
a = printf( "  %%    %X    %u    %x    %p    %c  \n", mx_u, mx_u, mx_u, 4218944, mx_c		);//printf("%d\n", a);
a = printf( "  %p    %c    %s    %u    %i    %x  \n", 4218944, mx_c, mx_s, mx_u, mx_i, mx_u	);//printf("%d\n", a);
a = printf( "  %i    %c    %%    %p    %u    %x  \n", mx_i, mx_c, 4218944, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %X    %%    %u    %c    %p    %s  \n", mx_u, mx_u, mx_c, 4218944, mx_s		);//printf("%d\n", a);
a = printf( "  %X    %i    %c    %u    %p    %s  \n", mx_u, mx_i, mx_c, mx_u, 4218944, mx_s	);//printf("%d\n", a);
a = printf( "  %p    %%    %c    %X    %u    %i  \n", 4218944, mx_c, mx_u, mx_u, mx_i		);//printf("%d\n", a);
a = printf( "  %s    %c    %i    %%    %p    %X  \n", mx_s, mx_c, mx_i, 4218944, mx_u		);//printf("%d\n", a);
a = printf( "  %p    %%    %c    %u    %s    %X  \n", 4218944, mx_c, mx_u, mx_s, mx_u		);//printf("%d\n", a);
a = printf( "  %x    %c    %%    %s    %X    %i  \n", mx_u, mx_c, mx_s, mx_u, mx_i		);//printf("%d\n", a);
a = printf( "  %%    %c    %i    %X    %s    %x  \n", mx_c, mx_i, mx_u, mx_s, mx_u		);//printf("%d\n", a);
a = printf( "  %i    %X    %%    %c    %u    %s  \n", mx_i, mx_u, mx_c, mx_u, mx_s		);//printf("%d\n", a);
a = printf( "  %p    %x    %c    %s    %u    %p  \n", 4218944, mx_u, mx_c, mx_s, mx_u, 4218944	);//printf("%d\n", a);
a = printf( "  %u    %p    %c    %X    %s    %p  \n", mx_u, 4218944, mx_c, mx_u, mx_s, 4218944	);//printf("%d\n", a);
a = printf( "  %p    %c    %u    %X    %s    %p  \n", 4218944, mx_c, mx_u, mx_u, mx_s, 4218944	);//printf("%d\n", a);
a = printf( "  %i    %u    %X    %p    %c    %p  \n", mx_i, mx_u, mx_u, 4218944, mx_c, 4218944	);//printf("%d\n", a);
a = printf( "  %i    %c    %p    %%    %X    %u  \n", mx_i, mx_c, 4218944, mx_u, mx_u		);//printf("%d\n", a);
a = printf( "  %s    %c    %i    %x    %p    %u  \n", mx_s, mx_c, mx_i, mx_u, 4218944, mx_u	);//printf("%d\n", a);
a = printf( "  %u    %s    %x    %p    %i    %c  \n", mx_u, mx_s, mx_u, 4218944, mx_i, mx_c	);//printf("%d\n", a);
a = printf( "  %u    %p    %X    %c    %%    %x  \n", mx_u, 4218944, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = printf( "  %c    %p    %X    %x    %%    %s  \n", mx_c, 4218944, mx_u, mx_u, mx_s		);//printf("%d\n", a);
a = printf( "  %x    %c    %s    %p    %u    %i  \n", mx_u, mx_c, mx_s, 4218944, mx_u, mx_i	);//printf("%d\n", a);
a = printf( "  %X    %p    %c    %%    %u    %i  \n", mx_u, 4218944, mx_c, mx_u, mx_i		);//printf("%d\n", a);
a = printf( "  %%    %i    %x    %p    %c    %s  \n", mx_i, mx_u, 4218944, mx_c, mx_s		);//printf("%d\n", a);
a = printf( "  %X    %p    %c    %s    %i    %u  \n", mx_u, 4218944, mx_c, mx_s, mx_i, mx_u	);//printf("%d\n", a);
a = printf( "  %u    %i    %p    %x    %s    %X  \n", mx_u, mx_i, 4218944, mx_u, mx_s, mx_u	);//printf("%d\n", a);
a = printf( "  %i    %s    %%    %p    %X    %c  \n", mx_i, mx_s, 4218944, mx_u, mx_c		);//printf("%d\n", a);
a = printf( "  %X    %p    %c    %u    %x    %i  \n", mx_u, 4218944, mx_c, mx_u, mx_u, mx_i	);//printf("%d\n", a);
*/
/*
a = ft_printf( "  %u    %%    %p    %x    %s    %i  \n", mx_u, &mx_i, mx_u, mx_s, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %x    %c    %X    %s    %u    %p  \n", mx_u, mx_c, mx_u, mx_s, mx_u, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %%    %i    %X    %p    %c    %s  \n", mx_i, mx_u, &mx_i, mx_c, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %u    %%    %s    %c    %x    %X  \n", mx_u, mx_s, mx_c, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %i    %c    %x    %u    %%    %X  \n", mx_i, mx_c, mx_u, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %c    %X    %i    %%    %s    %p  \n", mx_c, mx_u, mx_i, mx_s, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %p    %x    %i    %c    %s    %u  \n", &mx_i, mx_u, mx_i, mx_c, mx_s, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %i    %s    %%    %u    %c    %x  \n", mx_i, mx_s, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %X    %p    %s    %%    %u    %x  \n", mx_u, &mx_i, mx_s, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %c    %%    %u    %i    %x    %X  \n", mx_c, mx_u, mx_i, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %i    %p    %X    %u    %s    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %X    %c    %p    %x    %i    %u  \n", mx_u, mx_c, &mx_i, mx_u, mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %%    %i    %u    %s    %c    %X  \n", mx_i, mx_u, mx_s, mx_c, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %u    %c    %x    %s    %X    %i  \n", mx_u, mx_c, mx_u, mx_s, mx_u, mx_i	);//printf("%d\n", a);
a = ft_printf( "  %s    %p    %X    %c    %i    %x  \n", mx_s, &mx_i, mx_u, mx_c, mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %u    %c    %X    %x    %p    %s  \n", mx_u, mx_c, mx_u, mx_u, &mx_i, mx_s	);//printf("%d\n", a);
a = ft_printf( "  %c    %%    %i    %X    %u    %x  \n", mx_c, mx_i, mx_u, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %s    %%    %x    %X    %c    %u  \n", mx_s, mx_u, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %x    %s    %X    %%    %p    %i  \n", mx_u, mx_s, mx_u, &mx_i, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %%    %p    %i    %c    %x    %X  \n", &mx_i, mx_i, mx_c, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %c    %s    %%    %u    %p    %x  \n", mx_c, mx_s, mx_u, &mx_i, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %c    %i    %u    %s    %p    %x  \n", mx_c, mx_i, mx_u, mx_s, &mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %X    %x    %s    %c    %i    %u  \n", mx_u, mx_u, mx_s, mx_c, mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %x    %c    %X    %p    %s    %p  \n", mx_u, mx_c, mx_u, &mx_i, mx_s, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %X    %%    %i    %s    %p    %x  \n", mx_u, mx_i, mx_s, &mx_i, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %i    %p    %x    %c    %X    %p  \n", mx_i, &mx_i, mx_u, mx_c, mx_u, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %X    %c    %i    %u    %x    %p  \n", mx_u, mx_c, mx_i, mx_u, mx_u, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %i    %u    %c    %%    %X    %p  \n", mx_i, mx_u, mx_c, mx_u, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %s    %i    %c    %p    %x    %u  \n", mx_s, mx_i, mx_c, &mx_i, mx_u, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %p    %%    %x    %X    %i    %c  \n", &mx_i, mx_u, mx_u, mx_i, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %X    %i    %s    %%    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %%    %u    %p    %i    %X    %c  \n", mx_u, &mx_i, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %x    %X    %p    %s    %i    %c  \n", mx_u, mx_u, &mx_i, mx_s, mx_i, mx_c	);//printf("%d\n", a);
a = ft_printf( "  %c    %%    %s    %X    %x    %p  \n", mx_c, mx_s, mx_u, mx_u, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %x    %X    %p    %s    %i    %u  \n", mx_u, mx_u, &mx_i, mx_s, mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %p    %u    %s    %X    %c    %p  \n", &mx_i, mx_u, mx_s, mx_u, mx_c, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %X    %s    %x    %p    %%    %i  \n", mx_u, mx_s, mx_u, &mx_i, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %x    %s    %%    %p    %i    %c  \n", mx_u, mx_s, &mx_i, mx_i, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %s    %u    %x    %%    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %p    %i    %x    %%    %u    %X  \n", &mx_i, mx_i, mx_u, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %%    %c    %X    %p    %u    %x  \n", mx_c, mx_u, &mx_i, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %u    %c    %%    %p    %i    %s  \n", mx_u, mx_c, &mx_i, mx_i, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %%    %i    %s    %u    %c    %X  \n", mx_i, mx_s, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %%    %i    %u    %s    %X    %p  \n", mx_i, mx_u, mx_s, mx_u, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %s    %c    %X    %%    %i    %p  \n", mx_s, mx_c, mx_u, mx_i, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %x    %X    %u    %i    %%    %s  \n", mx_u, mx_u, mx_u, mx_i, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %x    %u    %s    %i    %p    %p  \n", mx_u, mx_u, mx_s, mx_i, &mx_i, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %X    %i    %s    %x    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, mx_u, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %c    %i    %%    %X    %p    %u  \n", mx_c, mx_i, mx_u, &mx_i, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %s    %u    %i    %X    %%    %c  \n", mx_s, mx_u, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %%    %p    %X    %i    %s    %x  \n", &mx_i, mx_u, mx_i, mx_s, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %i    %x    %p    %c    %u    %X  \n", mx_i, mx_u, &mx_i, mx_c, mx_u, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %X    %c    %%    %i    %x    %s  \n", mx_u, mx_c, mx_i, mx_u, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %x    %c    %u    %X    %p    %p  \n", mx_u, mx_c, mx_u, mx_u, &mx_i, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %p    %u    %c    %s    %i    %p  \n", &mx_i, mx_u, mx_c, mx_s, mx_i, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %x    %p    %s    %u    %%    %c  \n", mx_u, &mx_i, mx_s, mx_u, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %%    %i    %X    %p    %u    %s  \n", mx_i, mx_u, &mx_i, mx_u, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %%    %u    %c    %s    %i    %x  \n", mx_u, mx_c, mx_s, mx_i, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %c    %i    %u    %x    %s    %p  \n", mx_c, mx_i, mx_u, mx_u, mx_s, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %c    %i    %s    %u    %x    %p  \n", mx_c, mx_i, mx_s, mx_u, mx_u, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %u    %%    %x    %i    %X    %c  \n", mx_u, mx_u, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %x    %s    %u    %i    %c    %X  \n", mx_u, mx_s, mx_u, mx_i, mx_c, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %%    %c    %i    %p    %s    %X  \n", mx_c, mx_i, &mx_i, mx_s, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %s    %x    %%    %X    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %x    %X    %u    %c    %%    %i  \n", mx_u, mx_u, mx_u, mx_c, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %c    %%    %i    %p    %u    %X  \n", mx_c, mx_i, &mx_i, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %i    %c    %%    %u    %X    %p  \n", mx_i, mx_c, mx_u, mx_u, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %s    %i    %x    %u    %c    %p  \n", mx_s, mx_i, mx_u, mx_u, mx_c, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %s    %x    %c    %p    %u    %X  \n", mx_s, mx_u, mx_c, &mx_i, mx_u, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %%    %s    %p    %i    %X    %c  \n", mx_s, &mx_i, mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %x    %X    %i    %%    %s    %u  \n", mx_u, mx_u, mx_i, mx_s, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %s    %i    %X    %c    %%    %p  \n", mx_s, mx_i, mx_u, mx_c, &mx_i		);//printf("%d\n", a);
a = ft_printf( "  %x    %p    %c    %s    %X    %u  \n", mx_u, &mx_i, mx_c, mx_s, mx_u, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %%    %X    %u    %x    %p    %c  \n", mx_u, mx_u, mx_u, &mx_i, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %p    %c    %s    %u    %i    %x  \n", &mx_i, mx_c, mx_s, mx_u, mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %i    %c    %%    %p    %u    %x  \n", mx_i, mx_c, &mx_i, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %X    %%    %u    %c    %p    %s  \n", mx_u, mx_u, mx_c, &mx_i, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %X    %i    %c    %u    %p    %s  \n", mx_u, mx_i, mx_c, mx_u, &mx_i, mx_s	);//printf("%d\n", a);
a = ft_printf( "  %p    %%    %c    %X    %u    %i  \n", &mx_i, mx_c, mx_u, mx_u, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %s    %c    %i    %%    %p    %X  \n", mx_s, mx_c, mx_i, &mx_i, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %p    %%    %c    %u    %s    %X  \n", &mx_i, mx_c, mx_u, mx_s, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %x    %c    %%    %s    %X    %i  \n", mx_u, mx_c, mx_s, mx_u, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %%    %c    %i    %X    %s    %x  \n", mx_c, mx_i, mx_u, mx_s, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %i    %X    %%    %c    %u    %s  \n", mx_i, mx_u, mx_c, mx_u, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %p    %x    %c    %s    %u    %p  \n", &mx_i, mx_u, mx_c, mx_s, mx_u, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %u    %p    %c    %X    %s    %p  \n", mx_u, &mx_i, mx_c, mx_u, mx_s, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %p    %c    %u    %X    %s    %p  \n", &mx_i, mx_c, mx_u, mx_u, mx_s, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %i    %u    %X    %p    %c    %p  \n", mx_i, mx_u, mx_u, &mx_i, mx_c, &mx_i	);//printf("%d\n", a);
a = ft_printf( "  %i    %c    %p    %%    %X    %u  \n", mx_i, mx_c, &mx_i, mx_u, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %s    %c    %i    %x    %p    %u  \n", mx_s, mx_c, mx_i, mx_u, &mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %u    %s    %x    %p    %i    %c  \n", mx_u, mx_s, mx_u, &mx_i, mx_i, mx_c	);//printf("%d\n", a);
a = ft_printf( "  %u    %p    %X    %c    %%    %x  \n", mx_u, &mx_i, mx_u, mx_c, mx_u		);//printf("%d\n", a);
a = ft_printf( "  %c    %p    %X    %x    %%    %s  \n", mx_c, &mx_i, mx_u, mx_u, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %x    %c    %s    %p    %u    %i  \n", mx_u, mx_c, mx_s, &mx_i, mx_u, mx_i	);//printf("%d\n", a);
a = ft_printf( "  %X    %p    %c    %%    %u    %i  \n", mx_u, &mx_i, mx_c, mx_u, mx_i		);//printf("%d\n", a);
a = ft_printf( "  %%    %i    %x    %p    %c    %s  \n", mx_i, mx_u, &mx_i, mx_c, mx_s		);//printf("%d\n", a);
a = ft_printf( "  %X    %p    %c    %s    %i    %u  \n", mx_u, &mx_i, mx_c, mx_s, mx_i, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %u    %i    %p    %x    %s    %X  \n", mx_u, mx_i, &mx_i, mx_u, mx_s, mx_u	);//printf("%d\n", a);
a = ft_printf( "  %i    %s    %%    %p    %X    %c  \n", mx_i, mx_s, &mx_i, mx_u, mx_c		);//printf("%d\n", a);
a = ft_printf( "  %X    %p    %c    %u    %x    %i  \n", mx_u, &mx_i, mx_c, mx_u, mx_u, mx_i	);//printf("%d\n", a);
*/
	//printf("#%01.d#\n", 0);
	//printf("#%5d#\n", 0);
	//printf("#%05d#\n", 0);
	//printf("#%05.d#\n", 0);
	//printf("#%0 1.d#\n", 0);
	//ft_printf("%01.d", 0);
	//printf("%.0d", 5);
	//ft_printf("%.d", 0);
	//ft_printf("%.5s", s);
	//ft_printf(" %p ", -1);
	//printf("%7s\n", s);
	//ft_printf("%7s\n", s);
	//ft_printf(" %d ", -1);
	//ft_printf("#%1c#\n", '\0');
	//ft_printf("#%10c#", '\0');
	//printf("%X\n", 0);
	//ft_printf("%X\n", 0);
	//printf("%p", ((void*)0));
	//ft_printf("%p", ((void*)0));
	//ft_printf("#% s#\n", "");
	//printf("#% d#\n", 1);
	//printf("#% s#\n", "a");
	//ft_printf(" %+d ", 0);
	//ft_printf(" %.1s#\n", "a");
	/*int	orgi, test;
	//orgi = printf(" #%.1s# #%.2s# #%.3s# #%.4s# \n", " - ", "", "4", "");
	//test = ft_printf(" #%.1s# #%.2s# #%.3s# #%.4s# \n", " - ", "", "4", "");
	//orgi = printf(" #%.2s# \n", "");
	//test = ft_printf(" #%.2s# \n", "");
	orgi = printf(" #%.2s# \n", " - ");
	test = ft_printf(" #%.2s# \n", " - ");
	//test = ft_printf(" #%.1s# #%.2s# #%.3s# #%.4s# \n", " - ", "", "4", "");
	printf("orgi = %d, test = %d\n", orgi, test);*/
	//ft_printf(" %.1s#\n", "a");
	//ft_printf(" %.3s#\n", "a");
	//ft_printf(" %.1s#\n", "");
	//ft_printf(" %.3s#\n", "");
	//printf(" %.s #\n", "-");
	//ft_printf(" %.s #\n", "-");
	//printf(" %.s #\n", "sdjfposa-");
	//ft_printf(" %.s #\n", "sdjfposa-");
	//printf(" #%02d# \n", 1);
	//ft_printf(" #%02d# \n", 1);
	//printf(" #%02d# \n", -1);
	//ft_printf(" #%02d# \n", -1);
	//printf( "#%+9d#\n", 452 );
	//ft_printf( "#%+9d#\n", 452 );
	//ft_printf(" NULL %s NULL ", NULL);
	//ft_printf(" %p %p ", 0, 0);
	//ft_printf(" %x ", LONG_MIN);
	//ft_printf(" %%%% ");
	//ft_printf(" %-2c ", '0');
	//printf(" %-9X %-10X %-11X %-12X %-13X %-14X %-15X\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	//ft_printf(" %-9X %-10X %-11X %-12X %-13X %-14X %-15X\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	//ft_printf(" %x %x %x %x %x %x %x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
/*	printf(" NULL %s NULL ", NULL);
	
	int	orgi, test;
	orgi = printf("# %c %c %c #\n", '0', 0, '1');
	test = ft_printf("# %c %c %c #\n", '0', 0, '1');
	printf("orgi = %d, test = %d\n", orgi, test);

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
	unsigned int	aa = 10;
	printf("%%p : The void * pointer argument is printed in\n \
	hexadecimal  (as if by %%#x or %%#lx). %p %#x\n", &aa, &aa);
	
	ft_printf("%%p : The void * pointer argument is printed in\n \
	hexadecimal  (as if by %%#x or %%#lx). %p %#x\n", &aa, &aa);
	
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
	ft_printf("%%#x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %#x\n", 4242, 4242);
	printf("%%#X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %#X\n", 4242, 4242);
	ft_printf("%%#X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %#X\n", 4242, 4242);
	printf("%%#x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %#x\n", 0, 0);
	ft_printf("%%#x: Unsigned int -> unsigned hexadecimal (miniscule): %d: %#x\n", 0, 0);
	printf("%%#X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %#X\n", 0, 0);
	ft_printf("%%#X: Unsigned int -> unsigned hexadecimal (majuscule): %d: %#X\n", 0, 0);
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


	printf ("Integers: %+019i jsadlfd %+u oiodfsi %#0  -%  \n", -3456, 3456);
	ft_printf ("Integers: %+019i jsadlfd %+u oiodfsi %#0  -%  \n", -3456, 3456);
	
	printf( "#%+9d#\n", 452 );
	ft_printf( "#%+9d#\n", 452 );
	printf( "#%+09d#\n", 452 );
	ft_printf( "#%+09d#\n", 452 );
	printf( "#%+09.12d#\n", 452 );
	ft_printf( "#%+09.12d#\n", 452 );
	printf( "#%-019.29d#\n", 452 );
	ft_printf( "#%-019.29d#\n", 452 );
	printf( "#%-019.9d#\n", 452 );
	ft_printf( "#%-019.9d#\n", 452 );
	printf( "#%- 19.9d#\n", 452 );
	ft_printf( "#%- 19.9d#\n", 452 );
	printf( "#%- 19d#\n", 452 );
	ft_printf( "#%- 19d#\n", 452 );
	printf( "#%- .09d#\n", 452 );
	ft_printf( "#%- .09d#\n", 452 );
	printf( "#%- .09d#\n", -452 );
	ft_printf( "#%- .09d#\n", -452 );
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
	printf(":%.10s:\n", "Hello, world!");
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
*/
}
