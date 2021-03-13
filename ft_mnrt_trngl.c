/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_trngl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:16:24 by rburton           #+#    #+#             */
/*   Updated: 2021/03/12 10:07:31 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	trgn_null(t_trigon *trgn)
{
	// trgn->f = '\0';
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

void    nrml_make(t_trngl *trngl)
{
    v_make(&trngl->trgn.v_ab, &trngl->p1, &trngl->p2);
    v_make(&trngl->trgn.v_ac, &trngl->p1, &trngl->p3);
    v_crss_prdct(&trngl->n.xyz, &trngl->trgn.v_ab.nxyz, &trngl->trgn.v_ac.nxyz);
    v_fill(&trngl->n);
    v_n_prdct(&trngl->trgn.v_minus_f.xyz, &trngl->n.nxyz, -1);
	v_fill(&trngl->trgn.v_minus_f);
}

void    xp_calc(t_trngl *trngl, t_ray *ray)
{
    float       t;
    // t_vctr		v_op;

    t = pln_equation(&trngl->p1, &ray->tail_p, &trngl->n, &ray->vctr[ray->sgm]).t;
    if (fabsf(t) < INFINITY && t > 0)
	{
		v_null(&trngl->trgn.v_op);
		v_n_prdct(&trngl->trgn.v_op.xyz, &ray->vctr[ray->sgm].nxyz, t); //calculates vctr from ray origin point to p
		v_fill(&trngl->trgn.v_op);
		p_calc(&trngl->trgn.xp, &trngl->trgn.v_op.xyz, &ray->tail_p); //calculates p(x, y, z)
		trngl->trgn.t = t;
		// v_copy(&ray->vctr[ray->sgm], &trngl->trgn.v_op);
	}
}

void    trgn_converse(t_trngl *trngl)
{
    t_point tmp;

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

void    vctr2d_make(t_trngl *trngl)
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

void	is_in_trngl(t_trngl *trngl)
{
    float   r1;
    float   r2;
	int		i;

	i = 0;
    r1 = v2d_pd_prdct(&trngl->trgn._axp, &trngl->trgn._ab);
    r2 = v2d_pd_prdct(&trngl->trgn._ac, &trngl->trgn._ab);
	if (r1 <= 0 && r2 < 0)
		i++;
	r1 = v2d_pd_prdct(&trngl->trgn._bxp, &trngl->trgn._bc);
    r2 = v2d_pd_prdct(&trngl->trgn._ba, &trngl->trgn._bc);
	if (r1 <= 0 && r2 < 0)
		i++;
	r1 = v2d_pd_prdct(&trngl->trgn._cxp, &trngl->trgn._ca);
    r2 = v2d_pd_prdct(&trngl->trgn._cb, &trngl->trgn._ca);
	if (r1 <= 0 && r2 < 0)
		i++;
	if (i == 3)
		trngl->trgn.xp_in = '+';
}

void    trgn_make(t_trngl *trngl, t_ray *ray)
{
    nrml_make(trngl);
    look_at_mtrx(&trngl->trgn.lkt, &trngl->trgn.v_minus_f, &trngl->p1);
    nrml_trngl(trngl, ray);
    xp_calc(trngl, ray);
    trgn_converse(trngl);
    vctr2d_make(trngl);
    is_in_trngl(trngl);
}

void	trngl_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray)
{
	// t_vctr		o_p; //vctr from ray origin to the pln that is collinear to ray->vctr[0] and reaches p
	// float		t;
	
	trgn_null(&trngl->trgn);
	trgn_make(trngl, ray);
	// nrml_trngl(trngl, ray);
	// t = pln_equation(&trngl->p1, &ray->tail_p, &trngl->n, &ray->vctr[ray->sgm]).t; //3, 4
	// if (fabsf(t) < INFINITY && t > 0.00006)
	// {
	// 	v_null(&o_p);
	// 	v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, t); //calculates vctr from ray origin point to p
	// 	v_fill(&o_p);
	// 	p_calc(&trngl->trgn.xp, &o_p.xyz, &ray->tail_p); //calculates p(x, y, z)
	// 	trgn_make(trngl, ray);
	// }
	if (trngl->trgn.xp_in == '+' && trngl->trgn.t > 0 && trngl->trgn.t <= ray->dist && ray->sgm == 0)
	{
		ray->dist = trngl->trgn.t;
		ray->obj = 't';
		ray->nrst = lscn->n_trngl;
		v_copy(&ray->vctr[0], &trngl->trgn.v_op);
		p_copy(&ray->hit_p, &trngl->trgn.xp);
	}
	if (trngl->trgn.xp_in == '+' && ray->sgm == 1 && trngl->trgn.t > 0.000147 && ray->shdw != 'y' && trngl->trgn.t < ray->vctr[1].lngth)
		ray->shdw = 'y';
}

void 	check_trngls(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_trngl	*trngl;

	i = 0;
	lscn->n_trngl = lscn->frst_trngl;
	while (i < lscn->n_cntr.trngl)
	{
		trngl = lscn->n_trngl->content;
		trngl_intrsct(lscn, trngl, ray);
		if (lscn->n_trngl->next != NULL)
			lscn->n_trngl = lscn->n_trngl->next;
		i++;
	}
}