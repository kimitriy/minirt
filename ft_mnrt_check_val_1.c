/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check_val_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 08:14:57 by rburton           #+#    #+#             */
/*   Updated: 2021/03/22 12:31:27 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_val_color(t_prsr *np)
{
	float	lvl;
	int		r;
	int		g;
	int		b;

	if (ft_strchr(np->r, '.') != NULL || ft_strchr(np->g, '.') != NULL
		|| ft_strchr(np->b, '.') != NULL)
		err_message("Unable to apply color.");
	lvl = ft_atof(np->lvl);
	r = ft_atof(np->r);
	g = ft_atof(np->g);
	b = ft_atof(np->b);
	if (lvl < 0 || lvl > 1)
		err_message("Unable to apply brightness.");
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		err_message("Unable to apply color.");
}

void	check_val_coordinates(char *x, char *y, char *z, char v)
{
	double	dx;
	double	dy;
	double	dz;
	t_point	tp;
	t_point hp;
	t_vctr	tmp;

	dx = ft_atof(x);
	dy = ft_atof(y);
	dz = ft_atof(z);
	if ((dx < -1 * __FLT_MAX__) || (dx > __FLT_MAX__))
		err_message("Unable to apply coordinates.");
	if ((dy < -1 * __FLT_MAX__) || (dy > __FLT_MAX__))
		err_message("Unable to apply coordinates.");
	if ((dz < -1 * __FLT_MAX__) || (dz > __FLT_MAX__))
		err_message("Unable to apply coordinates.");
	if (v == 'v')
	{
		p_make(&tp, 0, 0, 0);
		p_make(&hp, dx, dy, dz);
		v_make(&tmp, &tp, &hp);
		if (tmp.lngth > 1 || tmp.lngth == 0)
			err_message("Unable to apply vector coordinates.");
	}
}

void	check_val_uint(char *n, int lim, char *mssg)
{
	int		tmp;

	if (ft_strchr(n, '.') != NULL)
		err_message(mssg);
	tmp = ft_atoi(n);
	if (tmp < 0 || tmp > lim)
		err_message(mssg);
}

void	check_val_float(char *n, char pos, char *mssg)
{
	double	tmp;

	tmp = ft_atof(n);
	if (tmp < (double)(-1 * __FLT_MAX__) || tmp > (double)__FLT_MAX__)
		err_message(mssg);
	if (pos == '+')
		if (tmp <= 0)
			err_message(mssg);
}