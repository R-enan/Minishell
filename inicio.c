#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct command
{
	char			*full;
	char			*only_command;
	char			*argument;
	char			***table;
	struct command 	*next;
} cmd;

void	free_table_quotes(char ***table)
{
	int	i;

	if (table)
	{
		i = 0;
		while(table[i])
		{
			free(table[i]);
			i++;
		}
		free(table);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	if (matrix)
	{
		i = 0;
		while(matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

char	***filtrar_aspas(char *comando)
{
	char 	***ret;
	char	*tmp;
	int		quotes;

	// Contar aspas
	tmp = comando;
	quotes = 0;
	while (*tmp)
	{
		if (*tmp == '\'' || *tmp == '"')
			quotes++;
		tmp++;
	}
	
	// Mallocar linhas matriz
	ret = (char ***) malloc((quotes / 2 + 1) * sizeof(char **));

	quotes = 0;
	// Inserir os valores
	while (*comando)
	{
		if (*comando == '"')
		{
			ret[quotes] = malloc(3 * sizeof(char **));
			ret[quotes][0] = "\"";
			ret[quotes][1] = comando;
			ret[quotes][2] = strchr(comando + 1, '"'); // NULL
			comando = ret[quotes][2];
			quotes++;
		}
		else if (*comando == '\'')
		{
			ret[quotes] = malloc(3 * sizeof(char **));
			ret[quotes][0] = "'";
			ret[quotes][1] = comando;
			ret[quotes][2] = strchr(comando + 1, '\'');
			comando = ret[quotes][2];
			quotes++;
		}	
		comando++;
	}
	ret[quotes] = NULL;
	// Retornar
	return (ret);
}

void	print_quoted_text(char ***table)
{
	int	i;
	char	*tmp;

	if (table && *table)
	{
		i = 0;
		while (table[i])
		{
			tmp = table[i][1] + 1;
			while (tmp < table[i][2])
			{
				printf("%c", *tmp);
				tmp++;
			}
			i++;
		}
		puts("");
	}
}

void	printar_tudo(char *comando, char ***table)
{
	int	line;
	char	*tmp;

	line = 0;
	while (*comando)
	{
		if (*comando == '"' || *comando == '\'')
		{
			tmp = table[line][1] + 1;
			while (tmp < table[line][2])
			{
				printf("%c", *tmp);
				tmp++;
			}
			comando = table[line][2];
			line++;
		}
		/* else if (*comando == '$')
		{
			// Expansão de variável
		} */
		else
			printf("%c", *comando);
		comando++;
	}
	
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = strlen(s);
	if (!s || !*s || !(start < s_len && len > 0))
		return (strdup(""));
	if (len >= s_len)
		sub = (char *)malloc((s_len - start + 1) * sizeof(char));
	else
		sub = (char *)malloc(len + 1);
	s += start;
	start = 0;
	while (len-- > 0 && s[start])
	{
		sub[start] = s[start];
		start++;
	}
	sub[start] = 0;
	return (sub);
}

void	ft_lstadd_back(cmd **lst, cmd *new)
{
	cmd	*aux;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = *lst;
	while(aux->next)
	{
		aux = aux->next;
	}
	aux->next = new;
}

void	separar_comandos(char *comando, cmd **lista)
{
	char	*tmp;
	char	*start;
	char	*end;
	cmd		*aux;

	start = comando;
	while (*comando)
	{
		if (*comando == '"')
		{
			tmp = strchr(comando + 1, '"'); // NULL
			comando = tmp;
		}
		else if (*comando == '\'')
		{
			tmp = strchr(comando + 1, '\'');
			comando = tmp;
		}
		else if (*comando == '|' || *(comando + 1) == '\0')
		{
			if (*(comando + 1) == '\0')
				end = comando;
			else
				end = comando - 1;
			aux = (cmd *)malloc(sizeof(cmd));
			aux->full = ft_substr(start, 0, end - start + 1); // Mallocado numa lista
			aux->table = filtrar_aspas(aux->full);
			aux->only_command = start;
			while (*aux->only_command == ' ')
				aux->only_command++;
			aux->argument = strchr(aux->only_command, ' ') + 1;
			aux->only_command = ft_substr(start, 0, strchr(aux->only_command, ' ') - aux->only_command);
			if (strchr(aux->only_command, '|'))
				aux->argument = ft_substr(aux->argument, 0, strchr(aux->only_command, '|') - aux->argument);
			else
				aux->argument = ft_substr(aux->argument, 0, strlen(aux->argument));
			aux->next = NULL;
			ft_lstadd_back(lista, aux);
			start = comando + 1;
		}
		comando++;
	}
}

void	free_list(cmd *lista)
{
	cmd	*aux;

	if (lista)
	{
		aux = lista;
		while (aux)
		{
			free(aux->full);
			free(aux->only_command);
			free_table_quotes(aux->table);
			aux = aux->next;
		}
		aux = lista;
		while (aux)
		{
			lista = lista->next;
			free(aux);
			aux = lista;
		}
	}
}

char	*ft_insert_str(char const *s, int start, char c)
{
	int		size;
	int		index;
	char	*str;

	size = 0;
	s += start;
	while (*s != c && *s)
	{
		size++;
		s++;
	}
	str = (char *)malloc(size + 1);
	str[size] = '\0';
	index = 0;
	s -= size;
	while (index < size)
		str[index++] = *s++;
	return (str);
}

int	*ft_count_lines(char const *s, char c, int *positions)
{
	size_t	lines;
	size_t	index;
	size_t	s_len;

	s_len = strlen(s);
	index = 0;
	lines = 0;
	if (s_len)
		positions = ((int *)malloc(((s_len / 2) + 1) * sizeof(int)));
	else
		positions = ((int *)malloc(2 * sizeof(int)));
	while (s[index] == c && s[index])
		index++;
	if (index != s_len)
		positions[++lines] = index;
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1])
			positions[++lines] = index + 1;
		index++;
	}
	positions[lines + 1] = -1;
	positions[0] = lines;
	return (positions);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		*positions;
	int		index;

	split = NULL;
	positions = NULL;
	positions = ft_count_lines(s, c, positions);
	split = (char **)malloc((positions[0] + 1) * sizeof(char *));
	index = 1;
	while (positions[index] != -1)
	{
		split[index - 1] = ft_insert_str(s, positions[index], c);
		index++;
	}
	split[index - 1] = NULL;
	free(positions);
	return (split);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	new_str_size;

	new_str_size = strlen(s1) + strlen(s2) + 1;
	new_str = calloc(new_str_size, sizeof(*new_str));
	if (!new_str)
		return (new_str);
	strlcat(new_str, s1, new_str_size);
	strlcat(new_str, s2, new_str_size);
	return (new_str);
}

int main(int argc, char **argv, char **envp)
{
	char	*teste;
	char	***table_quotes;
	cmd		*lista_comandos = NULL;
	cmd		*aux;

	teste = readline("Digite seu comando> ");
	// Filtrar aspas 
	// (Separar comando argumento)
	//print_quoted_text(table_quotes);
	printf("\n\nComando separado: \n");
	separar_comandos(teste, &lista_comandos);
	aux = lista_comandos;
	while(aux)
	{
		printf("Comando: %s\n", aux->full);
		for (int i = 0; aux->table[i]; i++)
		{
			for (int j = 0; j < 3; j++)
				printf("%d - %p\t", j, aux->table[i][j]);
			puts("");
		}
		aux = aux->next;
	}
	int i;
	for (i = 0; envp[i]; i++)
		if (!strncmp(envp[i], "PATH", 4))
			break;
	printf("\n\n%s\n\n", envp[i] );
	char	**splitado = ft_split(envp[i] + 5, ':');
	char	*aux_char;
	aux = lista_comandos;
	for (int linha = 0; splitado[linha]; linha++)
	{
		aux_char = ft_strjoin(splitado[linha], "/");
		free(splitado[linha]);
		splitado[linha] = aux_char;
		aux_char = ft_strjoin(splitado[linha], aux->only_command);
		free(splitado[linha]);
		splitado[linha] = aux_char;
	}
	int linha;
	for (linha = 0; splitado[linha]; linha++)
	{
		if (!access(splitado[linha], X_OK))
		{
			printf("Encontrou o arquivo em %s\n", splitado[linha]);
			break;
		}
		else
		{
			printf("Não existe %s\n",splitado[linha]);
		}
	}
	
	free(teste);
	printf ("\n\n\n\n\n\t\t\t===== EXECUTANDO O COMANDO =====\n\n\n\n");
	fflush(stdout);
	execve(splitado[linha], (char *[3]){"", aux->argument, 0}, envp); // Executa comando echo teste | grep e
	free_list(lista_comandos);
	free_matrix(splitado);
	//printf("retorno %d\n", access("/usr/bin/ls", X_OK));/ // Busca comando
	/* for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]); */

	//execve("/usr/bin/ls", (char *[3]){"", "-la", ""}, envp); // Executa comando echo teste | grep e
/* /usr/local/sbin/comando
/usr/local/bin/comando
/usr/sbin/comando
/usr/bin/comando
/sbin/comando
/bin/comando */
	return (0);
}

/*
struct pessoa
{
	char *nome;
	int idade;
	char *profissao;
	char *endereco;
};

typedef struct pessoa caracteristicas;

struct lista
{
	caracteristicas	pessoa;
	struct lista	*next;
};

typedef struct lista lista;

int	main(void)
{
	caracteristicas joao;
	caracteristicas pedro;
	caracteristicas jose;
	caracteristicas aurora;
	caracteristicas mariazinha;
	
	lista *comeco_lista;

	comeco_lista = (lista *) calloc(1, sizeof(lista));
	comeco_lista->pessoa.nome = "João";
	comeco_lista->pessoa.idade = 30;

	lista *proxima_pessoa;
	proxima_pessoa = (lista *) calloc(1, sizeof(lista));
	proxima_pessoa->pessoa.nome = "Mariazinha";
	proxima_pessoa->pessoa.idade = 28;

	lista *proxima_pessoa1;
	proxima_pessoa1 = (lista *) calloc(1, sizeof(lista));
	proxima_pessoa1->pessoa.nome = "Bruxa";
	proxima_pessoa1->pessoa.idade = 100;


	comeco_lista->next = proxima_pessoa;
	proxima_pessoa->next = proxima_pessoa1;

	lista *aux;

	aux = comeco_lista;

	printf("Nome: %s Idade: %d \n", aux->pessoa.nome, aux->pessoa.idade);
	aux = aux->next;
	printf("Nome: %s Idade: %d \n", aux->pessoa.nome, aux->pessoa.idade);
	//printf("Nome: %s Idade: %d \n", comeco_lista->next->pessoa.nome, comeco_lista->next->pessoa.idade);
	aux = aux->next;
	printf("Nome: %s Idade: %d \n", aux->pessoa.nome, aux->pessoa.idade);
	//printf("Nome: %s Idade: %d \n", comeco_lista->next->next->pessoa.nome, comeco_lista->next->next->pessoa.idade);
	return (0);
}
*/