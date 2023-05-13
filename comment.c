#include "header.h"

char	*find_comment(char *input)
{
	char	*start;

	start = input;
	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (*input == '#')
			if (input == start || ft_isspace(input[-1]))
				return (input);
		input++;
	}
	return (NULL);
}
