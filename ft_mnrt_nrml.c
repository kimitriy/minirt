/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_nrml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:28:48 by rburton           #+#    #+#             */
/*   Updated: 2021/02/11 21:41:37 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr)
{
    t_point o;
	t_vctr	oc; //vctr from .O(0,0,0) to .c of the sphr
	float	d_prdct;

	if (ray->sgm == 0)
	{	
		p_make(&o, 0, 0, 0);
		v_make(&oc, &o, &sphr->p);
		v_make(nrml, &sphr->p, &ray->hit_p);
	
	}
	else if (ray->sgm == 1)
	{
		v_make(nrml, &sphr->p, &ray->hit_p);
		v_opposite(nrml);
		v_fill(nrml);
	}
}


void	nrml_pln(t_pln *pln, t_ray *ray)
{
	t_point o;
	t_vctr	op; //vctr from .O(0,0,0) to .p of the pln
	float	d_prdct;

	if (ray->sgm == 0)
	{
		p_make(&o, 0, 0, 0);
		v_make(&op, &o, &pln->p);
		d_prdct = v_d_prdct(&pln->v.nxyz, &op.nxyz);
		if (d_prdct > 0)
		{
			v_opposite(&pln->v);
			v_fill(&pln->v);
		}
	}
}

void	nrml_trngl(t_polygon *plgn, t_trngl *trngl, t_ray *ray)
{
	t_point o;
	t_vctr	oa; //vctr from .O(0,0,0) to .a of the trngl
	float	d_prdct;

	if (ray->sgm == 0)
	{
		p_make(&o, 0, 0, 0);
		v_make(&oa, &o, &plgn->a);
		v_crss_prdct(&trngl->n.xyz, &plgn->cd_a.xyz, &plgn->a_b.xyz);
		v_fill(&trngl->n);
		d_prdct = v_d_prdct(&trngl->n.nxyz, &oa.nxyz);
		if (d_prdct > 0)
		{
			v_opposite(&trngl->n);
			v_fill(&trngl->n);
		}
	}
}