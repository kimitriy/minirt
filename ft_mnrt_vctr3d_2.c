/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr3d_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:11:38 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:13:22 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	v_fill(t_vctr *nvctr)
{
	if (nvctr->nxyz.x == 0 && nvctr->nxyz.y == 0 && nvctr->nxyz.z == 0)
	{
		v_lngth(nvctr);
		v_n(nvctr);
	}
	else if (nvctr->xyz.x == 0 && nvctr->xyz.y == 0 && nvctr->xyz.z == 0)
	{
		nvctr->xyz.x = nvctr->nxyz.x;
		nvctr->xyz.y = nvctr->nxyz.y;
		nvctr->xyz.z = nvctr->nxyz.z;
		v_lngth(nvctr);
	}
	else if (nvctr->xyz.x != nvctr->nxyz.x || nvctr->xyz.y !=
		nvctr->nxyz.y || nvctr->xyz.z != nvctr->nxyz.z)
	{
		nvctr->nxyz.x = 0;
		nvctr->nxyz.y = 0;
		nvctr->nxyz.z = 0;
		v_lngth(nvctr);
		v_n(nvctr);
	}
}

void	v_make(t_vctr *out, t_point *tail, t_point *head)
{
	v_null(out);
	v_xyz(&out->xyz, tail, head);
	v_fill(out);
}

void	v_copy(t_vctr *out, t_vctr *in)
{
	out->xyz.x = in->xyz.x;
	out->xyz.y = in->xyz.y;
	out->xyz.z = in->xyz.z;
	out->nxyz.x = in->nxyz.x;
	out->nxyz.y = in->nxyz.y;
	out->nxyz.z = in->nxyz.z;
	out->lngth = in->lngth;
}

void	v_sum(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2)
{
	out->x = vctr1->x + vctr2->x;
	out->y = vctr1->y + vctr2->y;
	out->z = vctr1->z + vctr2->z;
}
