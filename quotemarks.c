#include "header.h"

void	print_error(void)
{
	printf("Man! You just have ONE job. Close your quotes!\n");
	exit(2);
}

int	has_unclosed_quotes(char *input)
{
	char	quote;
	char	*tmp;

	while (*input)
	{
		if (*input == '\'')
		{
			tmp = strchr(input + 1, '\'');
			if (!tmp)
				return (1);
			input = tmp;
		}
		else if (*input == '"')
		{
			tmp = strchr(input + 1, '"');
			if (!tmp)
				return (1);
			input = tmp;
		}
		input++;
	}
	return (0);
}

// Fazer recursivo
void	remove_quotes(char *input)
{
	char	quote;

	while (*input)
	{
		quote = 0;
		while (*input && !quote)
		{
			if (*input == '\'' || *input == '"')
			{
				quote = *input;
				memmove(input, input + 1, strlen(input));
			}
			else
				input++;
		}
		while (*input && quote)
		{
			if (*input == quote)
			{
				memmove(input, input + 1, strlen(input));
				break ;
			}
			input++;
		}
	}
}

int	has_pipe(char *input)
{
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = strchr(input + 1, *input);
		else if (*input == '|')
			return (1);
		input++;
	}
	return (0);
}

t_env	*multiple_commands(char *input)
{
	t_env	*comandos;
	char	*start;
	char	*end;
	char	*string;

	comandos = NULL;
	start = input;
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = strchr(input + 1, *input);
		input++;
		if (*input == '|' || *input == 0)
		{
			end = input;
			string = ft_substr(start, 0, end - start);
			add_back(string, &comandos);
			if (*end)
				start = end + 1;
		}
	}
	return (comandos);
}
