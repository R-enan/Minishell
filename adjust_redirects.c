#include "header.h"



/*
int numberofredirects(char *str)
{
    int i;
    int count;
    int simbol;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '<' || str[i] == '>')
        {
            simbol = str[i];
            count++;
            i++;
            if (str[i] == simbol)
                i++;
        }
        i++;
    }
    return (count);
}
*/
int number_of_redirects(char *str)
{
	int		i;
	int		count;
	char	*quote_address;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_address = ft_strchr(&str[i + 1], str[i]);
			if (!quote_address)
				return (-1);
			i += quote_address - &str[i];
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			count++;
			if (str[i] == str[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}

char    *redirect(char *str)
{
	int		i;
	int		j;
	int		simbol;
	char	*newstr;
	char	*quote_address;

	i = 0;
	j = 0;
	newstr = ft_calloc(sizeof (char), ft_strlen(str) + number_of_redirects(str) + 1);
	while(str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_address = ft_strchr(&str[i + 1], str[i]);
			if (!quote_address)
				return (str);
			i += quote_address - &str[i];
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			simbol = str[i];
			if (i > 0 && ((str[i - 1] != ' ' && str[i + 1] == simbol) || (str[i - 1] != simbol && str[i] == simbol)))
			{
				newstr[j] = ' ';
				j++;
				newstr[j] = simbol;
				j++;
				i++;
			}
			else
			{
				newstr[j] = str[i];
				i++;
				j++;
			}
		}
		else
		{
			newstr[j] = str[i];
			j++;
			i++;
		}
	}
	free(str);
	return (newstr);
}


char    *one_after_redirects(char *str)
{
    char *start;
    char *aux;
    char *newstr;
    char *startnew;

    start = str;
    while(*str)
    {
        if (*str == '\'' || *str == '"')
            str = ft_strchr(str + 1, *str);
        if((*str == '<' && *(str + 1) != '<') || (*str == '>' && *(str + 1) != '>'))
        {
            if(*(str + 1) == ' ')
            {
                *(str + 1) = -5;
            }
            else
            {
                newstr = ft_calloc(1, (str - start) + ft_strlen(str + 1) + 3);
                startnew = newstr;
                aux = start;
                while(aux <= str)
                {
                    *newstr = *aux;
                    newstr++;
                    aux++; 
                }
                *newstr = -5;
                newstr++;
                while(*aux)
                {
                    *newstr = *aux;
                    newstr++;
                    aux++; 
                }
                *newstr = '\0';
                str = startnew + (str - start + 1);
                free (start);
                start = startnew;
            }
        }
        str++;
    }
    return (start);
}
