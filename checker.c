#include "header.h"

int	has_input_error(char *input)
{
	char	*comment;

	if (!input)
		return (1);
	comment = find_comment(input);
	if (comment)
		*comment = 0;
	if (has_unclosed_quotes(input))
	{
		write(1, "Quoting Error\n", 14);
		return (1);
	}
	// Check redirects
	return (0);
}