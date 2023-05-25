#include "header.h"

int	get_index(char c, char *s)
{
	int	index = 0;

	while(s && s[index])
	{
		if (c == s[index])
			return (index);
		index++;
	}
	return (-1);
}