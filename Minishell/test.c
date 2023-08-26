#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//#include <readline/readline.h>
//#include <readline/history.h>

void f()
{
	printf("stdout in f()");
}


// cc -g test.c -o test -lreadline && ./test
int main()
{
    int    fd;
    int	fout;
    fpos_t pos;

    printf("stdout, ");

    //fd = dup(fileno(stdout));
    fd = open("stdout.out", O_CREAT|O_WRONLY|O_TRUNC, 0664);

    f();

    //char	*com = readline("minishell$ ");
    fout = dup(STDOUT_FILENO);
    //dup2(STDOUT_FILENO, fout);
    dup2(fd, -1);
    perror("hi");
//    if (dup2(fd, -1) == -1)
//	    exit(1);
    //printf("%s\n", com);
    printf("%d %d\n", fout, STDOUT_FILENO);
    close(fd);

    dup2(fout, STDOUT_FILENO);
    printf("stdout again\n");
    return (0);
}

