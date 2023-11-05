#include "../../includes/expansion.h"
#include "../../includes/lexer.h"

void	remove_single_quote(char *str)
{
	ft_strtrim(str, "\"");
}

t_state	update_state(const char c, t_state prev)
{
	t_state	new;

	new = STATE_GENERAL;
	if (c == '\'')
	{
		if (prev == STATE_GENERAL)
			new = STATE_IN_QUOTE;
		else if (prev == STATE_IN_DOUBLE_QUOTE)
			new = STATE_IN_DOUBLE_QUOTE;
		else if (prev == STATE_IN_QUOTE)
			new = STATE_GENERAL;
	}
	else if (c == '\"')
	{
		if (prev == STATE_GENERAL)
			new = STATE_IN_DOUBLE_QUOTE;
		else if (prev == STATE_IN_QUOTE)
			new = STATE_IN_QUOTE;
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
	str = argv[1];
	size_t	len = 0;
	size_t	i = 0;
	t_state	state = STATE_GENERAL;

	// lenを数える
	while (str[i])
	{
		state = update_state(str[i], state);
		if (state == STATE_IN_QUOTE)
		{
			if (str[i] != '\'')
			{
				len++;
			}
		}
		else if (state == STATE_IN_DOUBLE_QUOTE)
		{
			if (str[i] != '\"')
			{
				len++;
			}
		}
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				len++;
			}
		}
		i++;
	}
	char	*trim = ft_calloc(len, sizeof(char));
	i = 0;
	size_t	j = 0;
	state = STATE_GENERAL;
	while (str[i])
	{
		state = update_state(str[i], state);
		if (state == STATE_IN_QUOTE)
		{
			if (str[i] != '\'')
			{
				trim[j] = str[i];
				j++;
			}
		}
		else if (state == STATE_IN_DOUBLE_QUOTE)
		{
			if (str[i] != '\"')
			{
				trim[j] = str[i];
				j++;
			}
		}
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				trim[j] = str[i];
				j++;
			}
		}
		i++;
	}
	printf("trim: %s\n", trim);
	return (0);
}
