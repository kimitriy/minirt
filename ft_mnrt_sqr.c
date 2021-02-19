/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sqr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:46:58 by rburton           #+#    #+#             */
/*   Updated: 2021/02/19 23:48:52 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	sqr_intrsct(t_scn *lscn, t_sqr *sqr, t_ray *ray)
{
	t_vctr		o_p; //vctr from ray origin to the pln that is collinear to ray->vctr[0] and reaches p
	t_point		p; //intersection point at which the ray intersects the pln
	float		t;	//distance between the ray origin point and the intersection piont

	nrml_sqr(sqr, ray);
	t = pln_equation(&sqr->p, &ray->tail_p, &sqr->v, &ray->vctr[ray->sgm]);
	if (fabsf(t) < INFINITY && t > 0.00006)
	{
		v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, t); //calculates vctr from ray origin point to p
		v_fill(&o_p);
		p_calc(&p, &o_p, &ray->tail_p); //calculates p(x, y, z)
	}
}

void 	check_sqrs(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_sqr	*sqr;

	i = 0;
	lscn->n_sqr = lscn->frst_sqr;
	while (i < lscn->n_cntr.sqr)
	{
		sqr = lscn->n_sqr->content;
		sqr_intrsct(lscn, sqr, ray);
		if (lscn->n_sqr->next != NULL)
			lscn->n_sqr = lscn->n_sqr->next;
		i++;
	}
}