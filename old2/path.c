#include "header.h"

char	*find_path(char *command, t_env *env)
{
	char	**path_list;
	char	*aux;
	long	index;
	size_t	command_len;

	path_list = ft_split(find_path("PATH", env), ':');
	if (!path_list)
		return (NULL);
	index = 0;
	command_len = ft_strlen(command);
	while (path_list[index])
	{
		aux = join_path(path_list[index], command);
		if (!aux)
		{
			free_matrix((void **)path_list);
			return (NULL);
		}
		free(path_list[index]);
		path_list[index++] = aux;
	}
	while (index--)
	{
		if (access(path_list[index], X_OK) == 0)
		{
			aux = ft_strdup(path_list[index]);
			return (aux);
		}
	}
	free_matrix( (void **)path_list);
	return (NULL);
}

char	*join_path(char *path_init, char *path_end)
{
	char	*path;

	path = malloc(ft_strlen(path_init) + ft_strlen(path_end) + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, path_init, ft_strlen(path_init) + 1);
	ft_strlcpy(path + ft_strlen(path), "/", 2);
	ft_strlcpy(path + ft_strlen(path), path_end, ft_strlen(path_end) + 1);
	return (path);
}
