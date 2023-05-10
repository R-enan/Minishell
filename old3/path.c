#include "header.h"

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
