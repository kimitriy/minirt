/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sqr_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:26:24 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 17:29:32 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	sqr_intrsct(t_scn *lscn, t_ray *ray, t_sqr *sqr, t_qdron *qdrn)
{
	t_vctr	o_p;

	nrml_sqr(sqr, ray);
	qdrn->t = pln_equation(&sqr->p, &ray->tail_p,
		&sqr->v, &ray->vctr[ray->sgm]).t;
	if (qdrn->t > 0 && qdrn->t < INFINITY)
	{
		v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, qdrn->t);
		v_fill(&o_p);
		if ((ray->sgm == 0) || (ray->sgm == 1 &&
			o_p.lngth < ray->vctr[1].lngth))
		{
			p_calc(&qdrn->xp, &o_p.xyz, &ray->tail_p);
			qdron_make(qdrn, sqr);
		}
	}
	if (qdrn->xp_in == '+' && ray->sgm == 0 && ray->dist > qdrn->t)
	{
		ray->dist = qdrn->t;
		ray->obj = 'q';
		ray->nrst = lscn->n_sqr;
		v_copy(&ray->vctr[0], &o_p);
		p_copy(&ray->hit_p, &qdrn->xp);
	}
}

void	check_sqrs(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_sqr	*sqr;
	t_qdron	qdrn;

	i = 0;
	lscn->n_sqr = lscn->frst_sqr;
	while (i < lscn->n_cntr.sqr)
	{
		sqr = lscn->n_sqr->content;
		qdron_null(&qdrn);
		sqr_intrsct(lscn, ray, sqr, &qdrn);
		is_in_shdw(&qdrn, sqr, ray);
		if (lscn->n_sqr->next != NULL)
			lscn->n_sqr = lscn->n_sqr->next;
		i++;
	}
}
