/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:55:50 by ktomoya           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:00 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_words(char const *big, char c)
{
	char const	*start;
	char		*word;
	size_t		len;

	start = big;
	len = 0;
	while (*big != '\0' && *big != c)
	{
		big++;
		len++;
	}
	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, start, len);
	return (word);
}

static char	**malloc_free(char **str, size_t end)
{
	size_t	start;

	start = 0;
	while (start < end)
	{
		free(str[start]);
		start++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	count = count_words(s, c);
	split = (char **)ft_calloc(count + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < count)
	{
		if (*s != c)
		{
			split[i] = get_words(s, c);
			if (split[i] == NULL)
				return (malloc_free(split, i));
			if (i + 1 != count)
				s = ft_strchr(s, c);
			i++;
		}
		s++;
	}
	return (split);
}
