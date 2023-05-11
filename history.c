#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;
    while(1)
    {
        input = readline("Minishell > ");
        if (!input)
        {
            free(input);
            continue ;
        }
        add_history(input);
    }
    return (0);  
}