#include "header.h"

/**
 * @param input Input typing by the user.
 * @brief Check if has a pipe that separate two commands. 
 **/
int	has_pipe(char *input)
{
	if (input == NULL)
		return (0); // Input error
	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		else if (*input == '|')
			return (1);
		input++;
	}
	return (0);
}

/**
 * @param input Input typing by the user.
 * @brief check is has some wrong pipes in commads separation
 * 
 * @note Some errors examples:
 * @note <many spaces> | echo hi
 * @note echo "hi"' that is the complement' | | grep o
 * @note echo "hi"' that is the complement' | grep o |
 **/
int	has_invalid_pipe(char *input)
{
	// falha com comando "ls | " (esse espaço depois do |)
	char	*tmp;

	while (input != NULL && *input == ' ')
		input++;
	if (input != NULL && *input == '|')
		return (1);
	while(input != NULL && *input != '\0')
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		else if (*input == '|')
		{
			tmp = ft_strchr(input + 1, *input); // tmp = input + 1; while (*tmp == ' ')++; if (*tmp == '|') return 1;
			if (tmp != NULL)
			{
				while (tmp-- > input)
					if (*tmp != ' ')
						break;
			}
			if (tmp == input || (*input == '|' && *(input + 1) == '\0'))
				return (1);
		}
		input++;
	}
	return (0);
}

/**
 * @param input Input typing by the user.
 * @brief Count the number of pipes that separates commands.
 **/
int	count_pipes(char *input)
{
	int	pipes;

	if (input == NULL)
		return (0);
	pipes = 0;
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		input++;
		if (*input == '|')
			pipes++;
	}
	return (pipes);
}
