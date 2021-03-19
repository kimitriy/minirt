/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:41:12 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 12:33:49 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cylon_null_1(t_cylon *cln)
{
	cln->_ch = INFINITY;
	cln->t1 = INFINITY;
	cln->t2 = INFINITY;
	cln->_oh = 0;
	cln->_hxp = 0;
	cln->_oxp1 = 0;
	cln->_oxp2 = 0;
	cln->angle = 0;
	cln->sin_alpha = 0;
}

void	cylon_null(t_cylon *cln)
{
	cylon_null_1(cln);
	p_make(&cln->o, 0, 0, 0);
	p_make(&cln->_o, 0, 0, 0);
	p_make(&cln->o_nb, 0, 0, 0);
	p_make(&cln->c, 0, 0, 0);
	p_make(&cln->_c, 0, 0, 0);
	p_make(&cln->d, 0, 0, 0);
	p_make(&cln->_d, 0, 0, 0);
	p2d_make(&cln->d_nb, 0, 0);
	p_make(&cln->xp1, 0, 0, 0);
	p_make(&cln->xp2, 0, 0, 0);
	p_make(&cln->p, 0, 0, 0);
	v2d_null(&cln->v_od_nb);
	v2d_null(&cln->v_oc_nb);
	v_null(&cln->v_d);
	v_null(&cln->v_od);
	v_null(&cln->v_oxp1);
	v_null(&cln->v_oxp2);
	v_null(&cln->v_o_c);
	v_null(&cln->v_p_c);
	pln_null(&cln->pln);
}

void	cap_pln(t_cylon *cln, t_cyl *cyl)
{
	t_cap_pln	t;

	v_null(&t.v_cc1);
	v_null(&t.v_cc2);
	v_n_prdct(&t.v_cc1.xyz, &cyl->v.nxyz, (-1) * cyl->h / 2);
	v_fill(&t.v_cc1);
	v_n_prdct(&t.v_cc2.xyz, &cyl->v.nxyz, cyl->h / 2);
	v_fill(&t.v_cc2);
	p_calc(&t.c1, &t.v_cc1.xyz, &cyl->p);
	p_calc(&t.c2, &t.v_cc2.xyz, &cyl->p);
	v_null(&t.v_oc1);
	v_null(&t.v_oc2);
	v_make(&t.v_oc1, &cln->o, &t.c1);
	v_make(&t.v_oc2, &cln->o, &t.c2);
	if (t.v_oc1.lngth <= t.v_oc2.lngth)
		pln_make(&cln->pln, &t.c1, &t.v_cc1);
	else
		pln_make(&cln->pln, &t.c2, &t.v_cc2);
	v_n_prdct(&cyl->v.xyz, &cln->pln.v.xyz, -1);
	v_fill(&cyl->v);
}

void	cylon_fill(t_cylon *cln, t_ray *ray, t_cyl *cyl)
{
	p_copy(&cln->c, &cyl->p);
	p_copy(&cln->o, &ray->tail_p);
	v_copy(&cln->v_d, &ray->vctr[ray->sgm]);
	p_calc(&cln->d, &cln->v_d.nxyz, &cln->o);
}

void	cylon_cnvrse(t_cylon *cln, t_look_at *lkt)
{
	t_vctr		vtmp;
	t_point		ptmp;

	mtrx4_x_point(&cln->o_nb, &lkt->m, &cln->o);
	mtrx4_x_point(&ptmp, &lkt->m, &cln->_d);
	cln->d_nb.x = ptmp.x;
	cln->d_nb.y = ptmp.y;
	v_null(&vtmp);
	mtrx4_x_vctr(&vtmp, &lkt->m, &cln->v_d.nxyz);
	cln->v_od_nb.xy.x = vtmp.xyz.x;
	cln->v_od_nb.xy.y = vtmp.xyz.y;
	v2d_lngth(&cln->v_od_nb);
	v_null(&vtmp);
	mtrx4_x_vctr(&vtmp, &lkt->m, &cln->v_o_c.xyz);
	cln->v_oc_nb.xy.x = vtmp.xyz.x;
	cln->v_oc_nb.xy.y = vtmp.xyz.y;
	v2d_lngth(&cln->v_oc_nb);
}
