/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_atof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:21:42 by rburton           #+#    #+#             */
/*   Updated: 2021/03/17 00:03:20 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	ft_atof(const char *str)
{
	double	r1;
	double	r2;
	int		l;
	int		sign;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
	r1 = (double)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	r2 = (double)ft_atoi(str);
	l = ft_strlen(str);
	while (l--)
		r2 /= 10;
	return (sign * (r1 + r2));
}
