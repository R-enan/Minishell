

#ifndef HEADER_H
# define HEADER_H

# include <err.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft.h"

# define IS_SPACE_SET " \t\r\v\f"

struct s_env
{
	char			*var;
	struct s_env	*next;
};

typedef struct s_env	t_env;

struct s_redirects
{
	t_env	*inputs_redirects;
	t_env	*outputs_redirects;
	int		fd_input;
	int		fd_output;
};

typedef struct s_redirects t_redirects;


void	set_input(t_redirects *redirects);
void	set_output(t_redirects *redirects);
void	kill_redirects(char ***command);

char	*one_after_redirects(char *str);
char	*redirect(char *str);
int 	number_of_redirects(char *str);
t_env	*get_redirects(char **command, char redirect);

void	free_matrix(void **matrix);
int		ft_isspace(char c);
char	*find_comment(char *input);
void	ft_adjust_delimiters(char *s, const char *set);
int		get_index(char c, char *s);
int		ft_is_in_set(char c, char const *set);

int		ft_has_invalid_pipe(char *input);

char	**ft_split_set(const char *s, const char *set);
char	**split_commands(char *input);

void	clean_inner_set(char *input, char *set);
void	restore_inner_set(char *input, char *set);

void	ft_modify_quotemarks_to_remove(char *input, char *set);
void	ft_removing_modified_quotemarks(char *input, char *set);

char	*expand_variables(char *input, t_env *env);
char	*tilde_expansion(char *input, t_env *env);
char	*get_value_of_var(char *var, t_env *env);

// checker.c
int		has_input_error(char *input);

// env.c
t_env	*pointer_to_list(char **envp);
char	**list_to_pointer(t_env *list);

// list.c
void	free_parent_list(t_env **list);
void	free_child_list(t_env **list);
void	add_back(t_env **list, t_env *node);
t_env	*new_node(char *value);
size_t	list_size(t_env *list);

// quotemarks.c
int		has_unclosed_quotes(char *input);
void	remove_quotes(char *input);

#endif