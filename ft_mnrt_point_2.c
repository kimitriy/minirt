/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_point_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:49:17 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 23:20:16 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int		p_is_equal(t_point *p1, t_point *p2)
{
	float		d;

	d = 0.000009;
	if (fabsf(p1->x - p2->x) < d && fabsf(p1->y - p2->y) <
		d && fabsf(p1->z - p2->z) < d)
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
	p_calc(&plnx->o, &plnx->orth.xyz, p);
}
