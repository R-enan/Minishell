#include <stdio.h>

int  check_if_unclosed_quotes(char *str)
{
    int quote;
    quote = 0;
    //ver se a str tem as aspa fechadas
    while(*str && !quote)
    {
        if(*str == '"' || *str == '\'')
            quote = *str;
        str++;
    }
    while(*str && quote)
    {
        if(*str == quote)
            quote = 0;
        str++;
    }
    if (*str)
        check_if_unclosed_quotes(str);
    else if (!quote)
    {
        printf("alguma aspa  foi fechada\n");
        return (0);
    }
    else
        printf("alguma aspa não foi fechada");
    return (0);
}

void    cut_off_quotes(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(str[i] != '\0')
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            j = i;
            while(str[j] != '\0')
            {
                str[j] = str[j + 1];
                j++;
            }
        }
        i++;
    }
    printf("%s\n", str);
}

int main (int argc, char **argv)
{
    cut_off_quotes(argv[1]);
    return 0;
}