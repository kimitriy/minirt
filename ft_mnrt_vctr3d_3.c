/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr3d_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:11:45 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:13:23 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	v_sbtrct(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2)
{
	out->x = vctr1->x - vctr2->x;
	out->y = vctr1->y - vctr2->y;
	out->z = vctr1->z - vctr2->z;
}

void	v_n_prdct(t_vxyz *out, t_vxyz *vxyz, float num)
{
	out->x = vxyz->x * num;
	out->y = vxyz->y * num;
	out->z = vxyz->z * num;
}

float	v_d_prdct(t_vxyz *xyz1, t_vxyz *xyz2)
{
	float	dt_prdct;

	dt_prdct = xyz1->x * xyz2->x + xyz1->y * xyz2->y + xyz1->z * xyz2->z;
	return (dt_prdct);
}

float	v_x_point_prdct(t_vxyz *xyz, t_point *p)
{
	float	prdct;

	prdct = xyz->x * p->x + xyz->y * p->y + xyz->z * p->z;
	return (prdct);
}
