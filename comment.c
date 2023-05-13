#include "header.h"

char	*find_comment(char *input)
{
	char	*start;

	start = input;
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (input && *input == '#')
			if (input == start || ft_isspace(input[-1]))
				return (input);
		if (input)
			input++;
	}
	return (NULL);
}
