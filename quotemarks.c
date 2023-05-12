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

/**
 * @param input Input typing by the user.
 * @brief Removes the sequenced quotes that don't have anything inside.
 * @note This function assumes that the input has a correct quotemarks (open and closed).
 **/
void	removing_useless_quotes(char *input)
{
	if (!input)
		return ;
	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			if (input[1] == *input)
				ft_memmove(input, input + 2, ft_strlen(input) - 1);
			else
				input = ft_strchr(input + 1, *input) + 1;
		}
		else
			input++;
	}
}
