#include "header.h"

/**
 * @param input Input typing by the user.
 * @brief Check if has a pipe that separate two commands. 
 **/ 
int has_pipe(char *input)
{
	if (!input)
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
int has_invalid_pipe(char *input)
{
	char	*tmp;

	while (*input == ' ')
		input++;
	if (*input == '|')
		return (1);
	while(*input)
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
