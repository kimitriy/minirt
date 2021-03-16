/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_nrml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:28:48 by rburton           #+#    #+#             */
/*   Updated: 2021/03/17 02:29:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr)
{
	t_vctr	oc; //vctr from .O(0,0,0) to .c of the sphr
	t_point	o;

	p_make(&o, 0, 0, 0);
	v_null(&oc);
	v_make(&oc, &o, &sphr->p);
	v_null(nrml);
	v_make(nrml, &sphr->p, &ray->hit_p);
	v_fill(nrml);
	if (oc.lngth < sphr->d / 2)
		v_opposite(nrml);
}

void	nrml_pln(t_pln *pln, t_ray *ray)
{
	t_point o;
	t_vctr	op; //vctr from .O(0,0,0) to .p of the pln
	float	d_prdct;

	if (ray->sgm == 0)
	{
		p_make(&o, 0, 0, 0);
		v_null(&op);
		v_make(&op, &o, &pln->p);
		v_fill(&op);
		d_prdct = v_d_prdct(&pln->v.nxyz, &op.nxyz);
		if (d_prdct > 0)
			v_opposite(&pln->v);
	}
}

void	nrml_trngl(t_trngl *trngl, t_ray *ray)
{
	float	d_prdct;

	if (/*p_is_equal(&ray->tail_p, &ray->hit_p) == 0 || */ray->sgm == 0)
	{
		v_fill(&trngl->n);
		d_prdct = v_d_prdct(&trngl->n.nxyz, &ray->vctr[0].nxyz);
		if (d_prdct > 0)
			v_opposite(&trngl->n);
	}
	else if (/*p_is_equal(&ray->tail_p, &ray->hit_p) == 0 || */ray->sgm == 1)
	{
		d_prdct = v_d_prdct(&trngl->n.nxyz, &ray->vctr[1].nxyz);
		if (d_prdct > 0)
			v_opposite(&trngl->n);
	}
}

void	nrml_sqr(t_sqr *sqr, t_ray *ray)
{
	float	d_prdct;

	if (ray->sgm == 0)
	{
		d_prdct = v_d_prdct(&sqr->v.nxyz, &ray->vctr[0].nxyz);
		if (d_prdct > 0)
			v_opposite(&sqr->v);
	}
	else if (ray->sgm == 1)
	{
		d_prdct = v_d_prdct(&sqr->v.nxyz, &ray->vctr[1].nxyz);
		if (d_prdct > 0)
			v_opposite(&sqr->v);
	}
}

void	nrml_cyl(t_cyl *cyl, t_ray *ray)
{
	float	d_prdct;
	
	if (ray->sgm == 0)
	{
		d_prdct = v_d_prdct(&cyl->n.nxyz, &ray->vctr[0].nxyz);
		if (d_prdct > 0)
			v_opposite(&cyl->n);
	}
	else if (ray->sgm == 1)
	{
		d_prdct = v_d_prdct(&cyl->n.nxyz, &ray->vctr[1].nxyz);
		if (d_prdct > 0)
			v_opposite(&cyl->n);
	}
}