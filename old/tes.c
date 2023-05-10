#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/************************************************************
 * 				Lista de Exercícios
 ************************************************************/
char *matrix[] = { 
	// Level 1
	
	"repeat_alpha",
	"rot_13", 
	"search_and_replace", 

	// Level 2
	"alpha_mirror",
	"camel_to_snake",
	"do_op",
	"ft_atoi",
	"ft_strcmp",
	"ft_strcspn",
	"ft_strdup",
	"ft_strpbrk",
	"ft_strrev",
	"ft_strspn",
	"inter",
	"is_power_of_2",
	"last_word",
	"max",
	"print_bits",
	"reverse_bits",
	"snake_to_camel",
	"swap_bits",
	"union",
	"wdmatch ",

	// Level 3

	"add_prime_sum",
	"epur_str",
	"expand_str",
	"ft_atoi_base",
	"ft_list_size",
	"ft_range",
	"ft_rrange",
	"hidenp",
	"lcm",
	"paramsum",
	"pgcd",
	"print_hex",
	"rstr_capitalizer",
	"str_capitalizer",
	"tab_mult ",

	// Level 4

	"flood_fill",
	"fprime",
	"ft_itoa",
	"ft_list_foreach",
	"ft_list_remove_if",
	"ft_split",
	"rev_wstr",
	"rostring",
	"sort_int_tab",
	"sort_list ",

	NULL
};

/************************************************************
 * 				Parte que faz o sorteio
 ************************************************************/

int	matrix_len(char **matrix)
{
	int	len = 0;

	while (matrix && *matrix)
	{
		len++;
		matrix++;
	}
	return (len);
}

void	sort_exercicio(char **matrix)
{
	int	exercicio_atual, exercicios_total = matrix_len(matrix);

	srand(time(NULL));
	if (exercicios_total)
	{
		exercicio_atual = rand() % exercicios_total;
		printf("Seu exercício atual é: \"%s\" ele está na posição %d/%d da matrix\n", matrix[exercicio_atual], exercicio_atual, exercicios_total);
	}
	else
		printf("Parabéns, você terminou tudo!\n");
}

int main(void)
{	
	sort_exercicio(matrix);
	return (0);
}