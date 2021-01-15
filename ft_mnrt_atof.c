/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_atof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:21:42 by rburton           #+#    #+#             */
/*   Updated: 2021/01/12 20:33:39 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	reset_ns(t_atof *ns)
{
	int		k;

	ns->j = 0;
	k = 0;
	while (k < 11)
		ns->digits[k++] = '\0';
}

t_atof	make_t_atof(void)
{
	t_atof	ns;

	ns.i = 0;
	ns.j = 0;
	ns.r = 0;
	ns.int_part = 0;
	ns.fract_part = 0;
	ns.sign = 1;
	ns.dot = '\0';
	reset_ns(&ns);
	ns.rv = 0;
	return (ns);
}

void	atof_prsr(const char *str, t_atof *ns)
{
	while ((ft_isdigit(str[ns->i]) == 1 || str[ns->i] == '.' || str[ns->i] == '-') && ns->dot != '.')
	{
		if (str[ns->i] == '-')
			ns->sign = -1;
		if (str[ns->i] != '.')
			ns->digits[ns->j++] = str[ns->i++];
		else if ((ns->dot = '.'))
			break ;
	}
	ns->int_part = ns->sign * (double)ft_atoi(ns->digits);
	ns->i++;
	reset_ns(ns);
	while (ft_isdigit(str[ns->i]) == 1 && ns->dot == '.')
	{
		if (str[ns->i] == '0' && ns->r == 0)
		{
			ns->digits[ns->j] = '1';
			ns->r = 1;
			ns->j++;
		}
		ns->digits[ns->j++] = str[ns->i++];
	}
	ns->fract_part = ft_atoi(ns->digits);
}

int		nbr_length(long long int n, int base)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= base)
	{
		n = n / base;
		i++;
	}
	i += 1;
	return (i);
}

int		ft_iterative_power(int nb, int power)
{
	int		i;
	int		output;

	if (power < 0)
		output = 0;
	else if (power == 0)
		output = 1;
	else
	{
		i = 1;
		output = nb;
		while (i < power)
		{
			output = output * nb;
			i++;
		}
	}
	return (output);
}

float	ft_atof(const char *str)
{
	t_atof	ns;
	
	ns = make_t_atof();
	atof_prsr(str, &ns);
	ns.rv = (double)ft_iterative_power(10, nbr_length(ns.fract_part, 10) - ns.r);
	ns.rv = (double)ns.fract_part / ns.rv - ns.r;
	ns.rv = ns.int_part >= 0 ? (ns.int_part + ns.rv) * ns.sign : (ns.int_part - ns.rv) * ns.sign;
	return ((float)ns.rv);
}