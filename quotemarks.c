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

/**
 * @param input Input typing by the user.
 * @brief Removes where the more external quotemark starts and where it ends.
 **/
void	remove_quotes(char *input)
{
	char	quote;

	while (*input)
	{
		quote = 0;
		while (*input && !quote)
		{
			if (*input == '\'' || *input == '"')
			{
				quote = *input;
				memmove(input, input + 1, strlen(input));
			}
			else
				input++;
		}
		while (*input && quote)
		{
			if (*input == quote)
			{
				memmove(input, input + 1, strlen(input));
				break ;
			}
			input++;
		}
	}
}

/*char	*remove_quotes_and_expand_vars(char *input)
{
	char	*start;
	char	*end;
	char	quote;

	start = input;
	end = input;
	quote = 0;
	while (*end)
	{
		if (*end == '\'' || *end == '"')
		{
			quote = *end;
			start = end;
			ft_memmove(end, end + 1, ft_strlen(end));
			while (*++end != quote)
				end++;
			ft_memmove(end, end + 1, ft_strlen(end));
		}
		if (quote == '"' || *end == '$')
		{
			// expand vars from 'start' to 'end'

		}
		end++;
	}
	return (remove_quotes_and_expand_vars()); // Chamada recursiva
}
*/
