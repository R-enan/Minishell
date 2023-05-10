#include "header.h"

t_env	*pointer_to_list(char **envp)
{
	t_env	*env;
	t_env	*list;

	if (envp == NULL)
		return (NULL);
	list = NULL;
	while (*envp)
	{
		env = new_node(*envp);
		if (env == NULL)
		{
			free_list(&list);
			return (NULL);
		}
		add_back(&list, env);
		envp++;
	}
	return (list);
}

char	**list_to_pointer(t_env *list)
{
	char	**pointer;
	size_t	index;

	index = list_size(list);
	if (index == 0)
		return (NULL);
	pointer = (char **)malloc(sizeof(char *) * (index + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (list)
	{
		pointer[index] = list->var;
		list = list->next;
		index++;
	}
	pointer[index] = NULL;
	return (pointer);
}
