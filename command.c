#include "header.h"

/***
 * @param c The char to check
 * @param set The string that contains the caracters to check
 * @brief This functions checks if that is a match with c and some characters in the set.
 * @return 1 if has a match, 0 otherwise
 */
int	ft_is_in_set(char c, char const *set)
{
	while (set && *set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

/***
 * @param s The string with the text to analyze
 * @param set A string with the set of characters that will be delimiters
 * @brief Adjusts the content of s to the format: <phrase> <delimiter> <phrase> 
 * by eliminating the excess of delimiters in the middle of s
 */
void	ft_adjust_delimiters(char *s, const char *set)
{
	char	*end;

	if (!s || !set)
		return ;
	end = s;
	while (ft_is_in_set(*end, set))
		end++;
	if (end != s)
		ft_memmove(s, end, ft_strlen(end) + 1);
	while (*s)
	{
		if (ft_is_in_set(*s, set))
		{
			end = s + 1;
			while (ft_is_in_set(*end, set))
				end++;
			if (!*end)
				*s = 0;
			else
				*s = ' ';
			if (s + 1 != end)
				ft_memmove(s + 1, end, ft_strlen(end) + 1);
		}
		s++;
	}
}

/**
 * @param s The string with the content to be analyzed
 * @param set The delimiters that separates words
 * @brief This function counts the words in s separated by the characters in set
 * @return The quantity of words in s; 0 if s is NULL; 1 if s is not NULL but set is
 */
int	ft_count_words(char *s, const char *set)
{
	int	words;

	if (!s || !*s)
		return (0);
	if (!set)
		return (1);
	words = 1;
	while (*s)
	{
		while (*s && !ft_is_in_set(*s, set))
			s++;
		words++;
		if (*s)
			s++;
	}
	return (words);
}

/**
 * @param str The string with the text to be explited
 * @param set The set with the delimiters characters
 * @param splited The mallocated double array to insert the splited string
 * @brief This function inserts in splited the strings without the delimiters.
 * @return A pointer to the begining of splited double array, NULL if some allocation fails
 */
char	**ft_insert_words(char *str, const char *set, char **splited)
{
	int	start;
	int	end;
	int	actual_word;

	start = 0;
	actual_word = 0;
	while (str[start])
	{
		end = start;
		while (str[end] && !ft_is_in_set(str[end], set))
			end++;
		splited[actual_word] = ft_substr(str, start, end - start);
		if (!splited[actual_word])
		{
			free_matrix((void **)splited);
			return (NULL);
		}
		start = end + ft_is_in_set(str[end], set);
		actual_word++;
	}
	splited[actual_word] = NULL;
	return (splited);
}

/**
 * @param s The string that will be splitted
 * @param set The characters that delimits the words
 * @brief This function splits the s string by eliminating the characters in set
 * @return A double array with the words without the delimiters; NULL if the allocation fails
 */
char	**ft_split_set(const char *s, const char *set)
{
	char	**splited;
	char	*copy;
	int		words;

	if (!s)
		return (NULL);
	copy = ft_strdup(s);
	if (!copy)
		return (NULL);
	ft_adjust_delimiters(copy, set);
	words = ft_count_words(copy, set);
	splited = (char **) ft_calloc((words + 1), sizeof(char *));
	if (!splited)
		return (NULL);
	splited = ft_insert_words(copy, set, splited);
	if (!splited)
		return (NULL);
	return (splited);
}
