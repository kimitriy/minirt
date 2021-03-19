/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_utls_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:30:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 18:34:17 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int			get_next_line(int fd, char **line)
{
	static char		buf;
	int				rv;

	if (!(*line = malloc(1)))
		return (-1);
	**line = 0;
	rv = w2l(fd, &buf, line);
	return (rv);
}

long int	ft_atoi(const char *str)
{
	size_t					i;
	int						sign;
	unsigned long long int	number;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= (-1);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	number > 9223372036854775807 && sign > 0 ? number = -1 : 0;
	number > 9223372036854775807 && sign < 0 ? number = 0 : 0;
	return (sign * (long int)number);
}

int			ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

int			ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

float		max_2floats(float f1, float f2)
{
	if (f1 >= f2)
		return (f1);
	else
		return (f2);
}
