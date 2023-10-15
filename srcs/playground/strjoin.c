#include <stdio.h>
#include <string.h>

void strjoin(const char* str1, const char* str2, char* result) {
	strcpy(result, str1);  // 最初の文字列をコピー
	strcat(result, str2);  // 2番目の文字列を連結
}

int	main()
{
	char	result[100];

	char	*s1 = "Hello, ";
	strcpy(result, s1);
	printf("%s\n", result);
	return (0);
}