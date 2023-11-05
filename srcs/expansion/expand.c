#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

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

size_t	count_unquoted_len(const char *quoted)
{
	size_t	i;
	size_t	len;
	t_state	state;

	i = 0;
	len = 0;
	state = STATE_GENERAL;
	while (quoted[i])
	{
		state = update_state(quoted[i], state);
		if (state == STATE_IN_QUOTE && quoted[i] != '\'')
		{
			len++;
		}
		else if (state == STATE_IN_DOUBLE_QUOTE && quoted[i] != '\"')
		{
			len++;
		}
		else if (state == STATE_GENERAL && (quoted[i] != '\'' && quoted[i] != '\"'))
		{
			len++;
		}
		i++;
	}
	return (len);
}

void	copy_unquoted(char *unquoted, const char *quoted)
{
	size_t	i;
	size_t	j;
	t_state	state;

	i = 0;
	j = 0;
	state = STATE_GENERAL;
	while (quoted[i])
	{
		state = update_state(quoted[i], state);
		if (state == STATE_IN_QUOTE && quoted[i] != '\'')
		{
			unquoted[j] = quoted[i];
			j++;
		}
		else if (state == STATE_IN_DOUBLE_QUOTE && quoted[i] != '\"')
		{
			unquoted[j] = quoted[i];
			j++;
		}
		else if (state == STATE_GENERAL && quoted[i] != '\'' && quoted[i] != '\"')
		{
			unquoted[j] = quoted[i];
			j++;
		}
		i++;
	}
}	

char	*trim_quoted(const char *quoted)
{
	char	*trimed;
	size_t	len = count_unquoted_len(quoted);

	trimed = ft_calloc(len + 1, sizeof(char));
	copy_unquoted(trimed, quoted);
	return (trimed);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*line;
	char		*trimed;
	t_env		env;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	env.head = NULL;
	if (env_init(&env, envp) != 0)
		return (FAILURE);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		else
			continue ;
		env.envp = env_to_envp(&env);
		trimed = trim_quoted(line);
		printf("trimed: %s\n", trimed);
		free_env_to_envp(env.envp);
		free((void *)line);
	}
	return (0);
}
