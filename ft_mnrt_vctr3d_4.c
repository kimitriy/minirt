/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr3d_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:11:52 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:13:25 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	v_crss_prdct(t_vxyz *out, t_vxyz *xyz1, t_vxyz *xyz2)
{
	out->x = xyz1->y * xyz2->z - xyz2->y * xyz1->z;
	out->y = -1 * (xyz1->x * xyz2->z - xyz2->x * xyz1->z);
	out->z = xyz1->x * xyz2->y - xyz2->x * xyz1->y;
}

float	v_angle(t_vctr *vctr1, t_vctr *vctr2)
{
	float	angle;
	float	dt_prdct;
	float	divider;
	float	sign;
	float	res;

	dt_prdct = v_d_prdct(&vctr1->xyz, &vctr2->xyz);
	divider = vctr1->lngth * vctr2->lngth;
	res = dt_prdct / divider;
	sign = 1;
	if (res < 0)
	{
		sign = -1;
		res *= -1;
	}
	angle = acosf(sign * min_2floats(1, res));
	return (angle);
}

void	v_opposite(t_vctr *vctr)
{
	v_n_prdct(&vctr->xyz, &vctr->xyz, -1);
	v_fill(vctr);
}

float	v_are_collinear(t_vctr *v1, t_vctr *v2)
{
	if (v_d_prdct(&v1->xyz, &v2->xyz) == 1 ||
		v_d_prdct(&v1->xyz, &v2->xyz) == -1)
		return (1);
	else
		return (0);
}
