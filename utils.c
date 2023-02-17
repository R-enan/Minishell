
#include "header.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*index;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	join = (char *)calloc(s1_len + s2_len + 1, 1);
	if (join == NULL)
		return (NULL);
	index = join;
	memcpy(index, s1, s1_len);
	index += strlen(s1);
	memcpy(index, s2, s2_len);
	return ((char *)join);
}

static char	*ft_insert_str(char const *s, int start, char c)
{
	int		size;
	int		index;
	char	*str;

	size = 0;
	s += start;
	while (*s != c && *s)
	{
		size++;
		s++;
	}
	str = (char *)malloc(size + 1);
	str[size] = '\0';
	index = 0;
	s -= size;
	while (index < size)
		str[index++] = *s++;
	return (str);
}

static int	*ft_count_lines(char const *s, char c, int *positions)
{
	size_t	lines;
	size_t	index;
	size_t	s_len;

	s_len = strlen(s);
	index = 0;
	lines = 0;
	if (s_len)
		positions = ((int *)malloc(((s_len / 2) + 1) * sizeof(int)));
	else
		positions = ((int *)malloc(2 * sizeof(int)));
	while (s[index] == c && s[index])
		index++;
	if (index != s_len)
		positions[++lines] = index;
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1])
			positions[++lines] = index + 1;
		index++;
	}
	positions[lines + 1] = -1;
	positions[0] = lines;
	return (positions);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		*positions;
	int		index;

	split = NULL;
	positions = NULL;
	positions = ft_count_lines(s, c, positions);
	split = (char **)malloc((positions[0] + 1) * sizeof(char *));
	index = 1;
	while (positions[index] != -1)
	{
		split[index - 1] = ft_insert_str(s, positions[index], c);
		index++;
	}
	split[index - 1] = NULL;
	free(positions);
	return (split);
}