/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr3d_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:26:21 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:13:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	v_xyz(t_vxyz *out, t_point *tail, t_point *head)
{
	out->x = head->x - tail->x;
	out->y = head->y - tail->y;
	out->z = head->z - tail->z;
}

void	v_lngth(t_vctr *nvctr)
{
	nvctr->lngth = sqrtf(powf(nvctr->xyz.x, 2) +
		powf(nvctr->xyz.y, 2) + powf(nvctr->xyz.z, 2));
}

void	v_n(t_vctr *nvctr)
{
	float	v_lngth;
	float	lngth_invrsn;

	v_lngth = sqrtf(powf(nvctr->nxyz.x, 2) +
		powf(nvctr->nxyz.y, 2) + powf(nvctr->nxyz.z, 2));
	if (roundf(v_lngth) != 1)
	{
		lngth_invrsn = 1 / nvctr->lngth;
		nvctr->nxyz.x = nvctr->xyz.x * lngth_invrsn;
		nvctr->nxyz.y = nvctr->xyz.y * lngth_invrsn;
		nvctr->nxyz.z = nvctr->xyz.z * lngth_invrsn;
	}
}

void	v_null(t_vctr *nvctr)
{
	nvctr->xyz.x = 0;
	nvctr->xyz.y = 0;
	nvctr->xyz.z = 0;
	nvctr->nxyz.x = 0;
	nvctr->nxyz.y = 0;
	nvctr->nxyz.z = 0;
	nvctr->lngth = 0;
}
