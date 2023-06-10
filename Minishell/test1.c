#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int	main()
{
	int fd;     // file descriptor
	char buffer[100];  // buffer to hold data to be written
	fd = open("filename.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		// Handle error if file couldn't be opened
		perror("open");
		return -1;  // or use appropriate error handling
	}
	char *data = "Hello, World!";
	ssize_t bytes_written = write(fd, data, strlen(data));
	return (0);
}
