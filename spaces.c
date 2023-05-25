#include "header.h"

void	clean_inner_set(char *input, char *set)
{
	int		replace;
	char	quote;

	if (!input || !set)
		return ;
	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input++;
			while (*input && *input != quote)
			{
				replace = get_index(*input, set);
				if (replace != -1)
					*input = (-replace) - 1;
				input++;
			}
		}
		input++;
	}
}

void	restore_inner_set(char *input, char *set)
{
	char	quote;

	if (!input || !set)
		return ;
	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input++;
			while (*input && *input != quote)
			{
				if (-*input > 0 && -(*input) <= (int)ft_strlen(IS_SPACE_SET))
					*input = set[-(*input + 1)];
				input++;
			}
		}
		input++;
	}
}
