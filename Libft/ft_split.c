/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:11:22 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/14 23:55:57 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

	s_len = ft_strlen(s);
	index = 0;
	lines = 0;
	if (s_len)
		positions = ((int *)malloc(((s_len) + 1) * sizeof(int)));
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

	if (!s)
		return (NULL);
	split = NULL;
	positions = NULL;
	positions = ft_count_lines(s, c, positions);
	split = (char **)malloc((positions[0] + 1) * sizeof(char *));
	if (!split)
	{
		free(positions);
		return (NULL);
	}
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

/*int	ft_count_lines(char const *s, char c)
{
	size_t	lines;

	lines = 1;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1))
			lines++;
		s++;
	}
	return (lines);
}

size_t	ft_get_next_ocurrence(const char *s, char c)
{
	size_t	index;

	index = 0;
	while (*s && *s != c)
	{
		index++;
		s++;
	}
	return (index);
}

size_t	advance_c(const char *s, char c)
{
	size_t	index;

	index = 0;
	while (s && *s && *s++ == c)
		index++;
	return (index);
}

char	*ft_cut_str(char const *s, char c)
{
	size_t	index;
	char	*split;

	index = ft_get_next_ocurrence(s, c) + 1;
	split = (char *)malloc(index-- * sizeof(char));
	split[index] = '\0';
	while (index--)
		split[index] = s[index];
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	lines;
	size_t	index;

	if (!s)
		return (NULL);
	index = 0;
	lines = ft_count_lines(s, c);
	split = (char **)malloc((lines + 1) * sizeof(char *));
	s += advance_c(s, c);
	while (index < lines)
	{
		split[index] = ft_cut_str(s, c);
		s += ft_strlen(split[index]) + 1;
		s += advance_c(s, c);
		index++;
	}
	split[index] = NULL;
	return (split);
} 
*/