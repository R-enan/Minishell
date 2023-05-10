#include "header.h"

void	clean_inner_spaces(char *input)
{
	char	quote;

	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input;
			while (*++input != quote)
				if (*input == ' ')
					*input = -1;
		}
		input++;
	}
}

void	restore_inner_spaces(char *input)
{
	while (input && *input)
	{
		if (*input == -1)
			*input = ' ';
		input++;
	}
}