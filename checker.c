#include "header.h"

int	has_input_error(char *input)
{
	char	*comment;

	if (!input)
		return (1);
	comment = find_comment(input);
	if (comment)
		*comment = 0;
	// Check if is only spaces without command
	// if (ft_is_only_spaces(input))
	//		return (1);
	if (ft_has_invalid_pipe(input))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	if (has_unclosed_quotes(input))
	{
		write(2, "Quoting Error\n", 14);
		return (1);
	}
	// Check redirects
	/* if (has_redirect_error(input))
	{
		write(2, "syntax error near unexpected token `<>?'\n", 39);
		return (1);
	} */
	return (0);
}
