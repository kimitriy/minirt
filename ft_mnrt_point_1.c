/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_point_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 21:32:54 by rburton           #+#    #+#             */
/*   Updated: 2021/03/20 12:08:01 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	p2d_make(t_2d_point *out, int x, int y)
{
	out->x = x;
	out->y = y;
}

void	p_make(t_point *out, float x, float y, float z)
{
	out->x = x;
	out->y = y;
	out->z = z;
}

void	p_calc(t_point *out, t_vxyz *vctr, t_point *tail)
{
	out->x = tail->x + vctr->x;
	out->y = tail->y + vctr->y;
	out->z = tail->z + vctr->z;
}

void	p_copy(t_point *out, t_point *in)
{
	out->x = in->x;
	out->y = in->y;
	out->z = in->z;
}

void	p3dt2d_conv(t_2d_point *out, float x, float y)
{
	out->x = x;
	out->y = y;
}
