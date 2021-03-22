/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check_val_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 08:14:57 by rburton           #+#    #+#             */
/*   Updated: 2021/03/22 16:15:12 by rburton          ###   ########.fr       */
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
	t_check_val_coordinates t;

	t.dx = ft_atof(x);
	t.dy = ft_atof(y);
	t.dz = ft_atof(z);
	if ((t.dx < -1 * __FLT_MAX__) || (t.dx > __FLT_MAX__))
		err_message("Unable to apply coordinates.");
	if ((t.dy < -1 * __FLT_MAX__) || (t.dy > __FLT_MAX__))
		err_message("Unable to apply coordinates.");
	if ((t.dz < -1 * __FLT_MAX__) || (t.dz > __FLT_MAX__))
		err_message("Unable to apply coordinates.");
	if (v == 'v')
	{
		p_make(&t.tp, 0, 0, 0);
		p_make(&t.hp, t.dx, t.dy, t.dz);
		v_make(&t.tmp, &t.tp, &t.hp);
		if (roundf(t.tmp.lngth * 100) / 100 > 1 || t.tmp.lngth == 0)
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
