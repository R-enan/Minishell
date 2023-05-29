#include <stdio.h>

void	teste(int a)
{
	printf("%d vezes eu tentei te ajudar.\n", a);
}

void	*retorna_funcao(void)
{
	return (teste);
}

int	main(int argc, char **argv)
{
	void (*f)(int);

	while (*argv++)
		printf("%s\n", *argv);

	f = retorna_funcao();
	f(3);
}