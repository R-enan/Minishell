#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <string.h>

struct s_lista
{
	int valor;
	struct s_lista *next;
};

typedef struct s_lista t_lista;


size_t	ft_strlen(char *c)
{
	size_t	len = 0;
	
	while (*c != '\0')
	{
		len++;
		c++;
	}
	printf("c = %d\n", c[0]);
	//printf("C = %c\n", c);
	return (len);
}

t_lista	*new_node(int user_value)
{
	t_lista	*temp;

	temp = malloc(sizeof(t_lista));
	temp->valor = user_value;
	temp->next = NULL;
	return (temp);
}


void	add_back(t_lista **lista, t_lista *novo_no)
{
	t_lista	*copy;

	if (*lista == NULL)
	{
		*lista = novo_no;
		return ;
	}
	copy = *lista;
	while (copy->next != NULL)
		copy = copy->next;
	copy->next = novo_no;
}


int	main(int a, char **v, char **envp)
{
	char	*path = "";
	if (chdir(path))
	{
		printf("\n\nFerrou tudo!\n\n");
		perror("");
	}
}