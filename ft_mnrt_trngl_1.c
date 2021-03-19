/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_trngl_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:16:24 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 18:21:11 by rburton          ###   ########.fr       */
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
	p2d_make(&trgn->_a, 0, 0);
	p2d_make(&trgn->_b, 0, 0);
	p2d_make(&trgn->_c, 0, 0);
	p2d_make(&trgn->_xp, 0, 0);
	v2d_null(&trgn->_ab);
	v2d_null(&trgn->_ac);
	v2d_null(&trgn->_axp);
	v2d_null(&trgn->_bc);
	v2d_null(&trgn->_ba);
	v2d_null(&trgn->_bxp);
	v2d_null(&trgn->_ca);
	v2d_null(&trgn->_cb);
	v2d_null(&trgn->_cxp);
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
	trngl->trgn._a.x = tmp.x;
	trngl->trgn._a.y = tmp.y;
	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->p2);
	trngl->trgn._b.x = tmp.x;
	trngl->trgn._b.y = tmp.y;
	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->p3);
	trngl->trgn._c.x = tmp.x;
	trngl->trgn._c.y = tmp.y;
	p_make(&tmp, 0, 0, 0);
	mtrx4_x_point(&tmp, &trngl->trgn.lkt.m, &trngl->trgn.xp);
	trngl->trgn._xp.x = tmp.x;
	trngl->trgn._xp.y = tmp.y;
}

void	vctr2d_make(t_trngl *trngl)
{
	v2d_make(&trngl->trgn._ab, &trngl->trgn._a, &trngl->trgn._b);
	v2d_make(&trngl->trgn._ac, &trngl->trgn._a, &trngl->trgn._c);
	v2d_make(&trngl->trgn._axp, &trngl->trgn._a, &trngl->trgn._xp);
	v2d_make(&trngl->trgn._bc, &trngl->trgn._b, &trngl->trgn._c);
	v2d_make(&trngl->trgn._ba, &trngl->trgn._b, &trngl->trgn._a);
	v2d_make(&trngl->trgn._bxp, &trngl->trgn._b, &trngl->trgn._xp);
	v2d_make(&trngl->trgn._ca, &trngl->trgn._c, &trngl->trgn._a);
	v2d_make(&trngl->trgn._cb, &trngl->trgn._c, &trngl->trgn._b);
	v2d_make(&trngl->trgn._cxp, &trngl->trgn._c, &trngl->trgn._xp);
}
