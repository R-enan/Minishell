#include "header.h"

/***
 * @param input The string with the command
 * @brief Searches the single quote or the double quote and, until the quote closes, set all inner spaces to -1.
 */
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

/***
 * @param input The string with the command
 * @brief Searches the single quote or the double quote and, until the quote closes, set all -1 characters to spaces.
 */
void	restore_inner_spaces(char *input)
{
	while (input && *input)
	{
		if (*input == -1)
			*input = ' ';
		input++;
	}
}