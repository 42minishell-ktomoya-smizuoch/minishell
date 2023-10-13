#include "../../includes/libft.h"

 int main() {
     char str[] = "/Users/kudoutomoya/.volta/bin:/usr/local/bin";
     char* token = strtok(str, ":");
     while (token != NULL) {
         printf("%s\n", token);
         token = strtok(NULL, ":");
     }
     printf("====================================\n");
     char str2[] = "/Users/kudoutomoya/.volta/bin:/usr/local/bin";
     char* token2 = ft_strtok(str2, ":");
     while (token2 != NULL) {
         printf("%s\n", token2);
         token2 = ft_strtok(NULL, ":");
     }
     return 0;
 }
