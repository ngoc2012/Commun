#include <stdio.h>
#include "GNL/get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main()
{
	char	*s;
	int	fd;
	int	i;

	//fd = open("GNL.c", O_RDONLY);
	//fd = open("GNL/gnlTester/files/42_no_nl", O_RDONLY);
	fd = open("GNL/gnlTester/files/41_no_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/41_with_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/43_no_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/43_nl", O_RDONLY);
	i = 0;
	while (i < 10)
	{
		//printf("main\n");
		s = get_next_line(fd); if (s) {printf("#%s#", s);} free(s);
		printf("====================\n");
		i++;
	}
	close(fd);
}
