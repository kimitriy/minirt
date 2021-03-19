/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:48:08 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 22:49:27 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	oxp_calc(t_cylon *cln, t_look_at *lkt)
{
	t_oxp_calc	t;

	v_crss_prdct(&t.v_ort.xyz, &cln->v_od.nxyz, &cln->pln.v.nxyz);
	v_fill(&t.v_ort);
	p_calc(&t.ort, &t.v_ort.xyz, &cln->o_p);
	mtrx4_x_point(&t.ort, &lkt->m, &t.ort);
	p2d_make(&t.ort_nb, t.ort.x, t.ort.y);
	p2d_make(&t.o_nb, cln->o_nb.x, cln->o_nb.y);
	p2d_make(&t.c_nb, 0, 0);
	v2d_make(&t.v_ort_o, &t.ort_nb, &t.o_nb);
	v2d_make(&t.v_ort_d, &t.ort_nb, &cln->d_nb);
	v2d_make(&t.v_ort_c, &t.ort_nb, &t.c_nb);
	t.tmp = v2d_pd_prdct(&t.v_ort_o, &t.v_ort_d) *
		v2d_pd_prdct(&t.v_ort_o, &t.v_ort_c);
	if (t.tmp < 0)
		cln->oxp1_p = cln->hxp_p - cln->oh_p;
	else if (t.tmp > 0)
		cln->oxp1_p = cln->hxp_p + cln->oh_p;
	else if (t.tmp == 0)
	{
		if (v2d_pd_prdct(&t.v_ort_o, &t.v_ort_c) == 0 && cln->v_od.lngth != 0)
			cln->oxp1_p = cln->hxp_p;
	}
	else
		cylon_null(cln);
}

void	case1_2(t_cylon *cln, t_look_at *lkt)
{
	oxp_calc(cln, lkt);
	cln->t1 = 0.999965 * cln->oxp1_p / cln->sin_alpha;
	xp_cyl(cln);
}

void	case3(t_cylon *cln)
{
	cln->oxp1_p = cln->oh_p - cln->hxp_p;
	cln->oxp2_p = cln->oh_p + cln->hxp_p;
	cln->t1 = 0.999965 * cln->oxp1_p / cln->sin_alpha;
	cln->t2 = 0.999965 * cln->oxp2_p / cln->sin_alpha;
	xp_cyl(cln);
}

void	case4(t_cylon *cln)
{
	cln->oxp1_p = cln->oh_p;
	cln->t1 = 0.999965 * cln->oxp1_p / cln->sin_alpha;
	xp_cyl(cln);
}

void	is_on_cyl(t_cylon *cln, t_cyl *cyl, t_look_at *lkt)
{
	t_point	tmp1;
	t_point	tmp2;

	mtrx4_x_point(&tmp1, &lkt->m, &cln->xp1);
	mtrx4_x_point(&tmp2, &lkt->m, &cln->xp2);
	if ((tmp1.z < 0 || tmp1.z > cyl->h) && (tmp2.z < 0 || tmp2.z > cyl->h))
		cylon_null(cln);
	else if ((tmp1.z < 0 || tmp1.z > cyl->h) &&
		(tmp2.z >= 0 && tmp2.z <= cyl->h))
	{
		cln->t1 = INFINITY;
		p_make(&cln->xp1, 0, 0, 0);
		v_null(&cln->v_oxp1);
	}
	else if ((tmp1.z >= 0 && tmp1.z <= cyl->h) &&
		(tmp2.z < 0 || tmp2.z > cyl->h))
	{
		cln->t2 = INFINITY;
		p_make(&cln->xp2, 0, 0, 0);
		v_null(&cln->v_oxp2);
	}
}
