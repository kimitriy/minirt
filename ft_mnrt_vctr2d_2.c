/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr2d_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:04:27 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:04:49 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	v2d_make(t_vctr2d *out, t_2d_point *tail, t_2d_point *head)
{
	v_xy(&out->xy, tail, head);
	v2d_lngth(out);
}

float	v2d_d_prdct(t_vxy *xy1, t_vxy *xy2)
{
	float	dt_prdct;

	dt_prdct = xy1->x * xy2->x + xy1->y * xy2->y;
	return (dt_prdct);
}

float	v2d_pd_prdct(t_vctr2d *v_d, t_vctr2d *v_oc)
{
	float	rv;

	rv = v_oc->xy.x * v_d->xy.y - v_d->xy.x * v_oc->xy.y;
	return (rv);
}
