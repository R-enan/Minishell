#include "header.h"

int	has_input_error(char *input)
{
	if (!input)
		return (1);
	if (has_unclosed_quotes(input))
	{
		write(1, "Quoting Error\n", 14);
		return (1);
	}
	return (0);
}