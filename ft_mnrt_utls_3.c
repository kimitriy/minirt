/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_utls_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:31:05 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 18:32:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	max_3floats(float a, float b, float c)
{
	float	max;

	if (a >= b && a >= c)
		max = a;
	if (b >= a && b >= c)
		max = b;
	if (c >= a && c >= b)
		max = c;
	return (max);
}

float	min_2floats(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	err_message(char *error)
{
	write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	exit(0);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		output;

	i = 0;
	output = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		else
			i++;
	}
	output = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (output);
}

void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}
