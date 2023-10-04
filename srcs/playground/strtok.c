#include <stdio.h>
#include <string.h>
#include <libc.h>

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}

int main(void)
{
	char str[] = "Hello,World,How,Are,You";
	char *token = strtok(str, ",");

	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ",");
	}
	return (0);
}
