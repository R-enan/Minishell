

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

struct s_env
{
	char			*var;
	struct s_env	*next;
};

typedef struct s_env t_env;

void	print_error(void);
int		has_unclosed_quotes(char *input);
void	remove_quotes(char *input);
int		has_pipe(char *input);
t_env	*multiple_commands(char *input);

void	execute(char *input, t_env *env);
void	clean_inner_spaces(char *input);
char	*read_input(char *terminal);
void	add_back(char *item, t_env **list);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif