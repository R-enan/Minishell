#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while(str[i] != '\0')
        i++;
    return (i);
}

int  check_if_unclosed_quotes(char *str)
{
    int quote;
    quote = 0;
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
    i = 0;

    while(str[i] != '\0')
    {
        if (str[i] == '"')
        {
            i++;
            while(str[i] != '"')
            {
                write(1, &str[i], 1);
                i++;
            }
            i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while(str[i] != '\'')
            {
                write(1, &str[i], 1);
                i++;
            }
            i++;
        }
        write(1, &str[i], 1);
        i++;
    }
}
#include <readline/readline.h>
int main (int argc, char **argv)
{
    char *frase;
    frase = "eu \"amo ch\'ocolate\" branco";
    frase = readline("> ");
    check_if_unclosed_quotes(frase);
    return 0;
}