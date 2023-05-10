/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:00:30 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/21 19:08:53 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

int	ft_atoi(const char *nptr)
{
	short int	signal;
	int			num;

	num = 0;
	while (ft_isspace(*nptr))
		nptr++;
	signal = (*nptr == '+' || ft_isdigit(*nptr)) - (*nptr == '-');
	nptr += (*nptr == '+' || *nptr == '-');
	while (ft_isdigit(*nptr))
		num = (num * 10) + (*nptr++ - '0');
	return (num * signal);
}
