#include "header.h"

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
	commands = (char **) malloc ((count_pipes(input) + 2) * sizeof(char*));
	if (commands == NULL)
		return (NULL);
	while (*input)
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
				free(commands);
				return (NULL);
			}
			line++;
			if (*input)
				start = input + 1;
		}
	}
	commands[line] = NULL;
	return (commands);
}
