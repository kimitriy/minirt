/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_trngl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:32:43 by rburton           #+#    #+#             */
/*   Updated: 2021/02/21 06:36:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	trgn_null(t_trigon *trgn)
{
	trgn->f = '\0';
	trgn->xp_in = '\0';
	p_make(&trgn->xp, 0, 0, 0);
	p_make(&trgn->a, 0, 0, 0);
	p_make(&trgn->b, 0, 0, 0);
	p_make(&trgn->c, 0, 0, 0);
	v_null(&trgn->a_b);
	v_null(&trgn->b_c);
	v_null(&trgn->c_a);
	v_null(&trgn->xp_a);
	v_null(&trgn->xp_b);
	v_null(&trgn->xp_c);
	trgn->prmtr = 0;
	trgn->prmtr1 = 0;
	trgn->prmtr2 = 0;
	trgn->prmtr3 = 0;
	trgn->area = 0;
	trgn->area1 = 0;
	trgn->area2 = 0;
	trgn->area3 = 0;
}

void	trgn_prmtr(t_trigon *trgn)
{
	trgn->prmtr = (trgn->a_b.lngth + trgn->b_c.lngth + trgn->c_a.lngth) / 2;
	trgn->prmtr1 = (trgn->xp_a.lngth + trgn->a_b.lngth + trgn->xp_b.lngth) / 2;
	trgn->prmtr2 = (trgn->xp_b.lngth + trgn->b_c.lngth + trgn->xp_c.lngth) / 2;
	trgn->prmtr3 = (trgn->xp_c.lngth + trgn->c_a.lngth + trgn->xp_a.lngth) / 2;
}

void	trgn_area(t_trigon *trgn)
{
	trgn->area = sqrtf(trgn->prmtr * (trgn->prmtr - trgn->a_b.lngth) * (trgn->prmtr - trgn->b_c.lngth) * (trgn->prmtr - trgn->c_a.lngth));
	trgn->area1 = sqrtf(trgn->prmtr1 * (trgn->prmtr1 - trgn->xp_a.lngth) * (trgn->prmtr1 - trgn->a_b.lngth) * (trgn->prmtr1 - trgn->xp_b.lngth));
	trgn->area2 = sqrtf(trgn->prmtr2 * (trgn->prmtr2 - trgn->xp_b.lngth) * (trgn->prmtr2 - trgn->b_c.lngth) * (trgn->prmtr2 - trgn->xp_c.lngth));
	trgn->area3 = sqrtf(trgn->prmtr3 * (trgn->prmtr3 - trgn->xp_c.lngth) * (trgn->prmtr3 - trgn->c_a.lngth) * (trgn->prmtr3 - trgn->xp_a.lngth));
}

void	is_in_trngl(t_trngl *trngl)
{
	if (trngl->trgn.area >= 0.9999 * (trngl->trgn.area1 + trngl->trgn.area2 + trngl->trgn.area3))
		trngl->trgn.xp_in = '+';
}

void	trgn_make(t_trngl *trngl, t_ray *ray)
{
	if (trngl->trgn.f != 'f')
	{
		p_copy(&trngl->trgn.a, &trngl->p1);
		p_copy(&trngl->trgn.b, &trngl->p2);
		p_copy(&trngl->trgn.c, &trngl->p3);
		v_make(&trngl->trgn.c_a, &trngl->trgn.c, &trngl->trgn.a);
		v_make(&trngl->trgn.a_b, &trngl->trgn.a, &trngl->trgn.b);
		v_make(&trngl->trgn.b_c, &trngl->trgn.b, &trngl->trgn.c);
		trngl->trgn.f = 'f';
	}
	else if (trngl->trgn.f == 'f')
	{
		v_make(&trngl->trgn.xp_a, &trngl->trgn.xp, &trngl->trgn.a);
		v_make(&trngl->trgn.xp_b, &trngl->trgn.xp, &trngl->trgn.b);
		v_make(&trngl->trgn.xp_c, &trngl->trgn.xp, &trngl->trgn.c);
		trgn_prmtr(&trngl->trgn);
		trgn_area(&trngl->trgn);
		is_in_trngl(trngl);
	}
}

void	trngl_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray)
{
	t_vctr		o_p; //vctr from ray origin to the pln that is collinear to ray->vctr[0] and reaches p
	float		t;
	
	trgn_null(&trngl->trgn);
	trgn_make(trngl, ray);
	nrml_trngl(trngl, ray);
	t = pln_equation(&trngl->p1, &ray->tail_p, &trngl->n, &ray->vctr[ray->sgm]); //3, 4
	if (fabsf(t) < INFINITY && t > 0.00006)
	{
		v_null(&o_p);
		v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, t); //calculates vctr from ray origin point to p
		v_fill(&o_p);
		p_calc(&trngl->trgn.xp, &o_p, &ray->tail_p); //calculates p(x, y, z)
		trgn_make(trngl, ray);
	}
	if (trngl->trgn.xp_in == '+' && t > 0 && t < ray->dist && ray->sgm == 0)
	{
		ray->dist = t;
		ray->obj = 't';
		ray->nrst = lscn->n_trngl;
		v_copy(&ray->vctr[0], &o_p);
		p_copy(&ray->hit_p, &trngl->trgn.xp);
	}
	if (trngl->trgn.xp_in == '+' && ray->sgm == 1 && t > 0.000147 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
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