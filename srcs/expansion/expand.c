#include "../../includes/expansion.h"
#include "../../includes/lexer.h"

void	remove_single_quote(char *str)
{
	ft_strtrim(str, "\"");
}

//t_state	update_state(const char c, enum e_state prev)
//{
//	enum e_state	new;
//
//	new = STATE_GENERAL;
//	if (prev == STATE_GENERAL)
//	{
//		if (c == '\'')
//			new = STATE_IN_QUOTE;
//		else if (c == '\"')
//			new = STATE_IN_DOUBLE_QUOTE;
//	}
//	else if (prev == STATE_IN_QUOTE)
//	{
//		if (c == '\'')
//			new = STATE_GENERAL;
//		else
//			new = STATE_IN_QUOTE;
//	}
//	else if (prev == STATE_IN_DOUBLE_QUOTE)
//	{
//		if (c == '\"')
//			new = STATE_GENERAL;
//		else
//			new = STATE_IN_DOUBLE_QUOTE;
//	}
//	return (new);
//}

t_state	update_state(const char c, t_state prev)
{
	t_state	new;

	new = STATE_GENERAL;
	if (c == '\'')
	{
		if (prev == STATE_GENERAL)
			new = STATE_IN_QUOTE;
		else if (prev == STATE_IN_DOUBLE_QUOTE)
			new = STATE_IN_QUOTE;
		else if (prev == STATE_IN_QUOTE)
			new = STATE_GENERAL;
	}
	else if (c == '\"')
	{
		if (prev == STATE_GENERAL)
			new = STATE_IN_DOUBLE_QUOTE;
		else if (prev == STATE_IN_QUOTE)
			new = STATE_IN_DOUBLE_QUOTE;
		else if (prev == STATE_IN_DOUBLE_QUOTE)
			new = STATE_GENERAL;
	}
	else
		new = prev;
	return (new);
}

int	main(int argc, char *argv[])
{
	char	*str;

	if (argc != 2)
		return (1);
	str = ft_substr(argv[1], 0, ft_strlen(argv[1]));
	size_t	len = 0;
	size_t	i = 0;
	t_state	state = STATE_GENERAL;

	// lenを数える
	while (str[i])
	{
		state = update_state(str[len], state);
		printf("str[%zu]: %c\n", i, str[i]);
		// シングルクウォートの中にいる処理
		if (state == STATE_IN_QUOTE)
		{
			printf("state is in quote.\n");
			if (str[i] != '\'')
			{
				printf("len++\n");
				len++;
			}
		}
		else if (state == STATE_IN_DOUBLE_QUOTE)
		{
			printf("state is in double quote.\n");
			if (str[i] != '\"')
			{
				len++;
			}
		}
		else
		{
			printf("state is general.\n");
			len++;
		}
		i++;
	}
	printf("len: %zu\n", len);
//		while (str[i])
//		{
//			if (str[i] != '\'')
//				len++;
//			i++;
//		}
//		char *trim = ft_calloc(len + 1, sizeof(char));
//		size_t	j = 0;
//		i = 0;
//		while (str[i])
//		{
//			while (str[i] == '\'')
//				i++;
//			if (str[i])
//			{
//				trim[j] = str[i];
//				j++;
//			}
//			i++;
//		}
//		printf("trim: %s\n", trim);
//		return (0);
//	}
//	else if (*str == '\"')
//		str = ft_strtrim
	free(str);
	return (0);
}