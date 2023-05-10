//main(c,v)char**v;{c==3?printf("%s %s\n",v[1],v[2]),exit(2):0;}
//main(int c,char**v){if(c==3){printf("%s %s\n",v[1],v[2]);return 2;}}
	//main(c,v)char**v;{c==3?exit(printf("%s %s\n",v[1],v[2])>0+1):0;}
	//main(c,v)char**v;{((void(*)())v-2)(v);}
//int main(int c,char**v){if(c==3){return ;}}
//int main(int c,char**v){if(c==3){printf("%s %s\n",v[1],v[2]);return 2;}}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

static int    is_part(char character, const char *reference)
{
	size_t    index;

	index = 0;
	while (reference[index] != '\0')
	{
		if (reference[index] == character)
			return (1);
		index++;
	}
	return (0);
}

char    *ft_strpbrk(const char *s1, const char *s2)
{
	size_t    index;

	index = 0;
	while (s1[index] != '\0')
	{
		if (is_part(s1[index], s2) == 1)
			return ((char *)&s1[index]);
		index++;
	}
	return (NULL);
}
/*
int main(int a, char **b, char **c)
{
	char	*teste = strdup("Teste");
	sleep(2);
	int	pid = fork();

	if (pid == 0)
	{
		teste[0] = 'F';
		printf("Filho: %s %p\n", teste, teste);
		fflush(stdout);
		execve("/usr/bin/ls", (char *[]) {"ls", "-a", NULL}, c);
	}
	else
	{
		wait(NULL);
		printf("pai: %s %p\n", teste, teste);
		fflush(stdout);
		//free(teste);
	}
	sleep(2);
	printf("Fora: %s %p\n", teste, teste);
	fflush(stdout);
	free(teste);
	execve("./minishell", (char *[]){"./minishell", NULL}, c);
	if (access("/bin", X_OK))
		printf("Não\n");
	else
		printf("Não Não\n");

}*/
#include <fcntl.h>
//#include <errno.h>

void	f(int x)
{
	printf("%d\n", x);
}
/*#include <stdio.h>

int	print(char *message)
{
	return (printf("%s",message));
}

int	read_num(int num)
{
	return (scanf("%d", &num), num);
}

int	is_even_sorry_i_mean_to_say_is_even_my_bad_the_real_name_is_is_not_even(int num)
{
	return (!(num % 2));
}

int	is_odd(int num)
{
	return (!is_even_sorry_i_mean_to_say_is_even_my_bad_the_real_name_is_is_not_even(num));
}
// Verifica se um número é ímpar
int	main (void)
{
	return (print("Digite um número: ") + print(is_odd(read_num(0)) ? "sim\n" : "não\n") + 19);
}*/

/*void	pri(void *p)
{
	printf("%d\n", *((void *)p));
	//printf("%p\n", (void *)(p[0]));
}

int	main()
{
	int	x = 4;
	void	*p = &x;
	pri(p);
}*/

static int is_whitespace(char c) {
    return (c == ' ' || ('\t' <= c && c <= '\r'));
}

static int	is_digit(char c)
{
	return ((c >= '0' && c <= '9'));
}

static int convert_recursively(char *a, unsigned int toi) {
    if (!*a || is_whitespace(*a) || !is_digit(*a)) return toi;
    int single_digit = *a - '0';
    toi = toi * 10 + single_digit;
    return convert_recursively(a + 1, toi);
}

int my_atoi(char *str) {
    while (is_whitespace(*str)) str++;
    int sign = *str == '-' ? -1 : 1;
    if (sign == -1 || *str == '+') str++;
    return (convert_recursively(str, 0) * sign);
}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int main(int a, char **v, char **e) 
{
	execve("minishell", (char *[]){NULL}, e);
}
	/*printf("Número de argumentos: %d\n", a);
	while (*v)
		printf("%s \n", *v++);*/
	//execve("/bin/ls", (char *[]){"/bin/ls", "-l", NULL}, e);
	/*int	errno;
	
	int fd = open("/root", O_RDONLY);
	if (fd < 0)
	{
		perror("Qualquer mensagem aí");
		printf("%d\n", errno);
		return (1);
	}*/
	/*char cwd[500];
	printf("Diretório: %s\n", getcwd(cwd,500));
	chdir(".");
	printf("Diretório: %s\n", getcwd(cwd,500));
	printf("Tes");
	fflush(stdout);
	sleep(1);
	printf("TEste\33[2K\r");
	printf("Teste\n");*/


/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ


C  O  N  G  R  A  T  U  L  A  T  I  O  N  S   O  N   D  E  C  O  D  I  N  G   T  H  I  S   L  I  N  E    T  H  E                L  E  T  T  E  R      I  S:
R  S  O  E  B  L  N  Z  A  Y  N  D  Q  O  T   Q  T   I  K  I  T  R  E  U  M   O  E  B  O   Y  E  U  M ,  N  K  G   A  Y  T  N   P  G  S  Z  N  M  B   R  T: K
15 4  1 24 10 11 20  5 15 24  6 21  2  1  1   2  6   5  6  6  5  14 22 7  6   21 23 19 22  13 22 7  8    20 3  2*/