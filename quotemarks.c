
#include "header.h"

int	has_unclosed_quotes(char *input)
{
    if (input == NULL)
        return (0); // Has a input error
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			input = ft_strchr(input + 1, '\'');
			if (!input)
				return (1);
		}
		else if (*input == '"')
		{
			input = ft_strchr(input + 1, '"');
			if (!input)
				return (1);
		}
		input++;
	}
	return (0);
}
