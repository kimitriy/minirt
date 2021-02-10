/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_nrml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:28:48 by rburton           #+#    #+#             */
/*   Updated: 2021/02/10 21:07:15 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr)
{
    if (ray->sgm == 0)
		v_make(nrml, &sphr->p, &ray->hit_p);
	else if (ray->sgm == 1)
	{
		v_make(nrml, &sphr->p, &ray->hit_p);
		v_opposite(nrml);
		v_fill(nrml);
	}
}


void	nrml_pln_sqr(t_pln *pln, t_ray *ray)
{
	float	angle;

	angle = v_angle(&pln->v, &ray->vctr[1]) * 180 / M_PI;
	if (angle > 90)
	{
		angle = 180 - angle;
		v_opposite(&pln->v);
		v_fill(&pln->v);
	}
	else if (angle < 90)
	{
		
		v_opposite(&pln->v);
		v_fill(&pln->v);
	}
}

void	nrml_trngl(t_polygon *plgn, t_trngl *trn, t_vctr *from_cam)
{
	float	angle;

	v_crss_prdct(&trn->n.xyz, &plgn->cd_a.xyz, &plgn->a_b.xyz);
	v_fill(&trn->n);
	angle = 180 - v_angle(from_cam, &trn->n) * 180 / M_PI;
	if (angle > 90)
	{
		v_opposite(&trn->n);
		v_fill(&trn->n);
	}
}