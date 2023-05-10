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
			tmp = ft_strchr(input + 1, *input);
			if (tmp != NULL)
			{
				while (tmp-- > input)
					if (*tmp != ' ')
						break;
			}
			if (tmp == input || (*input == '|' && *(input + 1) == '\0'))
				return (1);
		}
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

/**
 * @param input Input typing by the user.
 * @brief Splits the commands through the pipes.
 *
 * @note Some errors examples:
 * @note <many spaces> | echo hi
 * @note echo "hi"' that is the complement' | | grep o
 * @note echo "hi"' that is the complement' | grep o |
 **/
char	**split_commands(char *input)
{
	char	*start;
	char	**commands;
	int		line;

	if (input == NULL)
		return (NULL);
	start = input;
	line = 0;
	commands = (char **) malloc (count_pipes(input) + 2);
	if (commands == NULL)
		return (NULL);
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		input++;
		if (*input == '|' || *input == '\0')
		{
			commands[line] = ft_substr(start, 0, input - start);
			if (commands[line] == NULL)
			{
				while (--line >= 0)
					free(commands[line]);
				return (NULL);
			}
			line++;
			start = input + 1;
		}
	}
	commands[line] = NULL;
	return (commands);
}
