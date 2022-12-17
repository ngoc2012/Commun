#include <stdio.h>
#include "GNL/get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main()
{
	char	*s;
	int	fd;
	//int	fd1, fd2;
	int	i;

	//fd = open("GNL.c", O_RDONLY);
	//fd = open("GNL/gnlTester/files/empty", O_RDONLY);
	//fd = open("GNL/gnlTester/files/42_no_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/41_no_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/43_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/41_with_nl", O_RDONLY);
	//fd1 = open("GNL/gnlTester/files/43_no_nl", O_RDONLY);
	//fd = open("GNL/gnlTester/files/multiple_line_no_nl", O_RDONLY);
	fd = open("GNL/gnlTester/files/multiple_nlx5", O_RDONLY);
	//fd = open("GNL/gnlTester/files/41_with_nl", O_RDONLY);
	//s = get_next_line(1000); if (s) {printf("#%s#", s);} free(s);
	//s = get_next_line(fd); if (s) {printf("#%s#", s);} free(s);
	//s = get_next_line(fd1); if (s) {printf("#%s#", s);} free(s);
	//s = get_next_line(fd2); if (s) {printf("#%s#", s);} free(s);
	//s = get_next_line(fd2); if (s) {printf("#%s#", s);} free(s);
	//s = get_next_line(fd1); if (s) {printf("#%s#", s);} free(s);
	//s = get_next_line(fd); if (s) {printf("#%s#", s);} free(s);
	i = 0;
	//while (i < 100)
	while (i < 10)
	{
		//printf("main\n");
		//s = get_next_line(fd); if (s) {printf("%d", printf("#%s#", s) - 2);} free(s);
		s = get_next_line(fd); if (s) {printf("#%s#", s);} free(s);
		//s = get_next_line(fd1); if (s) {printf("#%s#", s);} free(s);
		//s = get_next_line(fd2); if (s) {printf("#%s#", s);} free(s);
		printf("====================\n");
		i++;
	}
	close(fd);
}
