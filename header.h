

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void	print_error(void);
int		has_unclosed_quotes(char *input);
void	remove_quotes(char *input);

void	execute(char *input);
void	clean_inner_spaces(char *input);
char	*read_input(char *terminal);

#endif