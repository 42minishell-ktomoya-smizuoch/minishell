#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// dup
//int	main(void)
//{
//	char buffer[1024];
//
//	int	fd1 = open("file1.txt", O_RDONLY);
//	printf ("fd1: %d\n", fd1);
//	int fd2 = dup(fd1);
//	printf ("fd2: %d\n", fd2);
//
//	read(fd1, buffer, 1024);
//	printf("buffer: %s\n", buffer);
//	read(fd2, buffer, 1024);
//	printf("buffer: %s\n", buffer);
//
//	close(fd1);
//	close(fd2);
//	return (0);
//}

// dup2
//int main(void)
//{
//	int fd1 = open("file1.txt", O_RDONLY);
//	int fd2 = open("file2.txt", O_RDONLY);
//	char buffer[1024];
//
//
//	dup2(fd1, fd2);
//	read(fd2, buffer, 1024);
//	printf("buffer: %s\n", buffer);
//
//	close(fd1);
//	close(fd2);
//	return (0);
//}

int main(void)
{
	int fd = open("file1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	int tty = open("/dev/tty", O_RDWR);

	dup2(fd, STDOUT_FILENO);
	printf("標準出力");
	fflush(stdout);
	close(fd);

	dup2(tty, STDOUT_FILENO);
	printf("標準出力");
	close(tty);
	return (0);
}