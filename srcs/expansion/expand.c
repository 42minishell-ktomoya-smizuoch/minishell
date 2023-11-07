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

size_t	count_env_len(const char **key_head, t_env *env)
{
	char		*key;
	const char	*key_end = *key_head;
	char		*value;
	size_t		len;

	while (ft_isalnum(*key_end) || *key_end == '_')
		key_end++;
	key = ft_substr(*key_head, 0, key_end - *key_head);
	value = search_env(key, env);
	free(key);
	if (value)
		len = ft_strlen(value);
	else
		len = 0;
	*key_head = key_end;
	return (len);
}

size_t	count_len(const char *line, t_env *env)
{
	// 1文字ずつ走査する
	size_t	len = 0;
	t_state	state = STATE_GENERAL;
	while (*line)
	{
		state = update_state(*line, state);
		if (state == STATE_IN_QUOTE)
		{
			if (*line != '\'')
				len++;
		}
		else if (state == STATE_IN_DOUBLE_QUOTE)
		{
			if (*line == '$')
			{
				if (ft_isalnum(line[1]) || line[1] == '_')
				{
					line++;
					len += count_env_len(&line, env);
					continue ;
				}
				else
					len++;
			}
			else if (*line != '\"')
				len++;
		}
		else if (state == STATE_GENERAL)
		{
			if (*line == '$')
			{
				if (ft_isalnum(line[1]) || line[1] == '_')
				{
					line++;
					len += count_env_len(&line, env);
					continue ;
				}
			}
			else if (*line != '\'' && *line != '\"')
				len++;
		}
		line++;
	}
	return (len);
}

void	copy_env(char **dst, const char **src, t_env *env)
{
	const char	*src_nptr = *src;
	char		*dst_nptr = *dst;
	char		*key;
	const char	*value;

	while (ft_isalnum(*src_nptr) || *src_nptr == '_')
		src_nptr++;
	key = ft_substr(*src, 0, src_nptr - *src);
	*src = src_nptr;
	value = search_env(key, env);
	if (!value)
		return ;
	while (*value)
	{
		*dst_nptr = *value;
		dst_nptr++;
		value++;
	}
	*dst = dst_nptr;
}

void	copy_expand(char *dst, const char *src, t_env *env)
{
	t_state	state = STATE_GENERAL;

	while (*src)
	{
		state = update_state(*src, state);
		if (state == STATE_IN_QUOTE)
		{
			if (*src != '\'')
			{
				*dst = *src;
				dst++;
			}
		}
		else if (state == STATE_IN_DOUBLE_QUOTE)
		{
			if (*src == '$')
			{
				if (ft_isalnum(src[1]) || src[1] == '_')
				{
					src++;
					copy_env(&dst, &src, env);
					continue ;
				}
				else
				{
					*dst = *src;
					dst++;
				}
			}
			else if (*src != '\"')
			{
				*dst = *src;
				dst++;
			}
		}
		else
		{
			if (*src == '$')
			{
				if (ft_isalnum(src[1]) || src[1] == '_')
				{
					src++;
					copy_env(&dst, &src, env);
					continue ;
				}
			}
			else if (*src != '\'' && *src != '\"')
			{
				*dst = *src;
				dst++;
			}
		}
		src++;
	}
}

char	*expand_node(const char *line, t_env *env)
{
	char	*expanded;
	size_t	len = count_len(line, env);
	
	expanded = ft_calloc(len + 1, sizeof(char));
	copy_expand(expanded, line, env);
	return (expanded);
}

t_node	*expand(t_node *ast, t_env *env)
{
	char	*unexpanded;
	if (!ast)
		return (NULL);
	if (ast && ast->kind == NODE_PIPE)
	{
		expand(ast->left, env);
		expand(ast->right, env);
	}
	else if (ast && ast->kind == NODE_ARGUMENT)
	{
		unexpanded = ft_substr(ast->str, 0, ast->len);
		ast->expand = expand_node(unexpanded, env);
		// printf("ast->expand: %s\n", ast->expand);
		free(unexpanded);
		expand(ast->right, env);
	}
	return (ast);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	const char	*line;
// 	t_token		*token;
// 	t_node		*ast;
// 	t_env		env;

// 	(void)argv;
// 	if (argc != 1)
// 		return (FAILURE);
// 	env.head = NULL;
// 	if (env_init(&env, envp) != 0)
// 		return (FAILURE);
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			write(1, "exit\n", 5);
// 			exit(0);
// 		}
// 		else if (*line)
// 			add_history(line);
// 		else
// 			continue ;
// 		env.envp = env_to_envp(&env);
// 		token = lexer(line);
// 		if (!token)
// 		{
// 			free((void *)line);
// 			continue ;
// 		}
// 		ast = parser(token);
// 		if (!ast)
// 		{
// 			free((void *)line);
// 			continue ;
// 		}
// 		ast = expand(ast, &env);
// 		print_ast(ast);
// 		free_env_to_envp(env.envp);
// 		free((void *)line);
// 	}
// 	return (0);
// }
