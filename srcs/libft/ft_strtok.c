/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kudoutomoya <kudoutomoya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:04:37 by kudoutomoya       #+#    #+#             */
/*   Updated: 2023/10/12 15:27:25 by kudoutomoya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// char	*ft_strtok(char *s1, const char *s2)
// {
// 	static char	*next_start;
// 	char		*token;

// 	if (s1 != NULL)
// 		next_start = s1;
// 	while (*next_start && ft_strchr(s2, *next_start))
// 		next_start++;
// 	if (next_start == NULL || *next_start == '\0')
// 		return (NULL);
// 	token = next_start;
// 	while (*next_start)
// 	{
// 		if (ft_strchr(s2, *next_start))
// 			break ;
// 		next_start++;
// 	}
// 	if (*next_start)
// 	{
// 		*next_start = '\0';
// 		next_start++;
// 	}
// 	else
// 		next_start = NULL;
// 	return (token);
// }

char    *ft_strtok(char *s, const char *sep)
{
	static char *p;

	if (s == NULL)
	{
		s = p;
		if (s == NULL)
			return (NULL);
	}
	s += ft_strspn(s, sep);
	if (*s == '\0')
	{
		p = NULL;
		return (p);
	}
	p = s + ft_strcspn(s, sep);
	if (*p)
	{
		*p = '\0';
		p++;
	}
	else
		p = NULL;
	return (s);
}

// int main() {
//     char str[] = "Hello, world!";
//     char* token = ft_strtok(str, " ,!");
//     while (token != NULL) {
//         printf("%s\n", token);
//         token = ft_strtok(NULL, " ,!");
//     }
//     printf("====================================\n");
//     char str2[] = "Hello, world!";
//     char* token2 = strtok(str2, " ,!");
//     while (token2 != NULL) {
//         printf("%s\n", token2);
//         token2 = strtok(NULL, " ,!");
//     }
//     return 0;
// }