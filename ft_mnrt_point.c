/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 21:32:54 by rburton           #+#    #+#             */
/*   Updated: 2021/03/09 14:38:50 by rburton          ###   ########.fr       */
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

int		p_is_equal(t_point *p1, t_point *p2)
{
	float		d;

	d = 0.000009;
	if (fabsf(p1->x - p2->x) < d && fabsf(p1->y - p2->y) < d && fabsf(p1->z - p2->z) < d)
		return (1);
	else
		return (0);
}

void	p2pln_prjctn(t_plnx *plnx, t_pln *pln, t_point *p)
{
	float	d1;
	float	d2;
	float	d3;

	d1 = (pln->p.x - p->x) * pln->v.nxyz.x;
	d2 = (pln->p.y - p->y) * pln->v.nxyz.y;
	d3 = (pln->p.z - p->z) * pln->v.nxyz.z;
	d1 = d1 + d2 + d3;
	v_null(&plnx->orth);
	v_n_prdct(&plnx->orth.xyz, &pln->v.nxyz, d1);
	v_fill(&plnx->orth);
	p_calc(&plnx->_o, &plnx->orth.xyz, p);
}