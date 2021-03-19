/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_trngl_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:16:24 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 22:38:31 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	trgn_null(t_trigon *trgn)
{
	trgn->xp_in = '\0';
	p_make(&trgn->xp, 0, 0, 0);
	v_null(&trgn->v_ab);
	v_null(&trgn->v_ac);
	v_null(&trgn->v_op);
	v_null(&trgn->v_minus_f);
	null_lookat(&trgn->lkt);
	p2d_make(&trgn->p2_a, 0, 0);
	p2d_make(&trgn->p2_b, 0, 0);
	p2d_make(&trgn->p2_c, 0, 0);
	p2d_make(&trgn->p2_xp, 0, 0);
	v2d_null(&trgn->v2_ab);
	v2d_null(&trgn->v2_ac);
	v2d_null(&trgn->v2_axp);
	v2d_null(&trgn->v2_bc);
	v2d_null(&trgn->v2_ba);
	v2d_null(&trgn->v2_bxp);
	v2d_null(&trgn->v2_ca);
	v2d_null(&trgn->v2_cb);
	v2d_null(&trgn->v2_cxp);
}

void	nrml_make(t_trngl *trngl)
{
	v_make(&trngl->trgn.v_ab, &trngl->p1, &trngl->p2);
	v_make(&trngl->trgn.v_ac, &trngl->p1, &trngl->p3);
	v_crss_prdct(&trngl->n.xyz, &trngl->trgn.v_ab.nxyz, &trngl->trgn.v_ac.nxyz);
	v_fill(&trngl->n);
	v_n_prdct(&trngl->trgn.v_minus_f.xyz, &trngl->n.nxyz, -1);
	v_fill(&trngl->trgn.v_minus_f);
}

void	xp_calc(t_trngl *trngl, t_ray *ray)
{
	float	t;

	t = pln_equation(&trngl->p1, &ray->tail_p,
		&trngl->n, &ray->vctr[ray->sgm]).t;
	if (fabsf(t) < INFINITY && t > 0)
	{
		v_null(&trngl->trgn.v_op);
		v_n_prdct(&trngl->trgn.v_op.xyz, &ray->vctr[ray->sgm].nxyz, t);
		p_calc(&trngl->trgn.xp, &trngl->trgn.v_op.xyz, &ray->tail_p);
		trngl->trgn.t = t;
	}
}

void	trgn_converse(t_trngl *trngl)
{
	t_point	tmp;

	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->p1);
	trngl->trgn.p2_a.x = tmp.x;
	trngl->trgn.p2_a.y = tmp.y;
	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->p2);
	trngl->trgn.p2_b.x = tmp.x;
	trngl->trgn.p2_b.y = tmp.y;
	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->p3);
	trngl->trgn.p2_c.x = tmp.x;
	trngl->trgn.p2_c.y = tmp.y;
	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->trgn.xp);
	trngl->trgn.p2_xp.x = tmp.x;
	trngl->trgn.p2_xp.y = tmp.y;
}

void	vctr2d_make(t_trngl *trngl)
{
	v2d_make(&trngl->trgn.v2_ab, &trngl->trgn.p2_a, &trngl->trgn.p2_b);
	v2d_make(&trngl->trgn.v2_ac, &trngl->trgn.p2_a, &trngl->trgn.p2_c);
	v2d_make(&trngl->trgn.v2_axp, &trngl->trgn.p2_a, &trngl->trgn.p2_xp);
	v2d_make(&trngl->trgn.v2_bc, &trngl->trgn.p2_b, &trngl->trgn.p2_c);
	v2d_make(&trngl->trgn.v2_ba, &trngl->trgn.p2_b, &trngl->trgn.p2_a);
	v2d_make(&trngl->trgn.v2_bxp, &trngl->trgn.p2_b, &trngl->trgn.p2_xp);
	v2d_make(&trngl->trgn.v2_ca, &trngl->trgn.p2_c, &trngl->trgn.p2_a);
	v2d_make(&trngl->trgn.v2_cb, &trngl->trgn.p2_c, &trngl->trgn.p2_b);
	v2d_make(&trngl->trgn.v2_cxp, &trngl->trgn.p2_c, &trngl->trgn.p2_xp);
}
