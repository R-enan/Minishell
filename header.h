

#ifndef HEADER_H
# define HEADER_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "libft.h"

struct s_env
{
	char			*var;
	struct s_env	*next;
};

typedef struct s_env t_env;

void	free_matrix(void **matrix);

// checker.c
int		has_input_error(char *input);

// env.c
t_env	*env_build(char **envp);
char	**list_to_pointer(t_env *list);

// list.c
void	free_list(t_env **list);
void	add_back(t_env **list, t_env *node);
t_env	*new_node(char *value);
size_t	list_size(t_env *list);

// quovtemarks.c
int		has_unclosed_quotes(char *input);
void	remove_quotes(char *input);
void	removing_useless_quotes(char *input);

#endif