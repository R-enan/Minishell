#include "header.h"

/**
 * @param input Input typing by the user.
 * @brief Checks that each open quote has another pair to close it.
 **/
int	has_unclosed_quotes(char *input)
{
	if (input == NULL)
		return (-1); // Has a input error
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			input = ft_strchr(input + 1, '\'');
			if (input == NULL)
				return (1);
		}
		else if (*input == '"')
		{
			input = ft_strchr(input + 1, '"');
			if (input == NULL)
				return (1);
		}
		input++;
	}
	return (0);
}
