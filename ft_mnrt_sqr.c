/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sqr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:46:58 by rburton           #+#    #+#             */
/*   Updated: 2021/03/11 15:05:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	qdron_null(t_qdron *qdrn)
{
	qdrn->xp_in = '\0';
	qdrn->alpha = 0;
	qdrn->t = INFINITY;
	qdrn->x = 0;
	qdrn->y = 0;
	p_make(&qdrn->xp, 0, 0, 0);
	v_null(&qdrn->vTMP);
	v_null(&qdrn->vR);
	v_null(&qdrn->vUP);
	v_null(&qdrn->vCXP);
}

void	qdron_make(t_qdron *qdrn, t_sqr *sqr)
{
	t_look_at	lkt;

	v_copy(&lkt.vTMP, &sqr->v_tmp);
	lkt.tmp = '+';
	look_at_mtrx(&lkt, &sqr->v, &sqr->p);
	v_copy(&qdrn->vTMP, &lkt.vTMP);
	v_copy(&qdrn->vR, &lkt.vR);
	v_copy(&qdrn->vUP, &lkt.vUP);
	v_make(&qdrn->vCXP, &sqr->p, &qdrn->xp); //creates vCA
	qdrn->alpha = v_angle(&qdrn->vR, &qdrn->vCXP);
	qdrn->x = qdrn->vCXP.lngth * cosf(qdrn->alpha);
	qdrn->y = qdrn->vCXP.lngth * sinf(qdrn->alpha);
}

void	is_in_sqr(t_qdron *qdrn,t_sqr *sqr)
{
	if (fabsf(qdrn->x) <= sqr->side / 2 && fabsf(qdrn->y) <= sqr->side / 2)
		qdrn->xp_in = '+';
}

void	is_in_shdw(t_qdron *qdrn, t_sqr *sqr, t_ray *ray)
{
	if (qdrn->xp_in == '+' && ray->sgm == 1 && qdrn->t < ray->vctr[1].lngth) // the ray reflected from other objects intersetcs sqr
 		ray->shdw = 'y'; //the sqr casts a shadow 
	else if (qdrn->xp_in == '+' && ray->sgm == 1 && v_d_prdct(&sqr->v.nxyz, &ray->vctr[1].nxyz) < 0) // a lght is above or under the pln of the sqr, so that it cannot lit a visible surface of the sqr
		ray->shdw = 'y'; //unlit surface of the sqr is in the shadow
}

void	sqr_intrsct(t_scn *lscn, t_sqr *sqr, t_ray *ray)
{
	t_vctr		o_p; //vctr from ray origin to the pln that is collinear to ray->vctr[0] and reaches p
	t_qdron		qdrn;

	qdron_null(&qdrn);
	
	nrml_sqr(sqr, ray);
	qdrn.t = pln_equation(&sqr->p, &ray->tail_p, &sqr->v, &ray->vctr[ray->sgm]).t;
	if (qdrn.t > 0 && qdrn.t < INFINITY)
	{
		v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, qdrn.t); //calculates vctr from ray origin point to the intrsct_p
		v_fill(&o_p);
		if ((ray->sgm == 0) || (ray->sgm == 1 && o_p.lngth < ray->vctr[1].lngth))
		{
			p_calc(&qdrn.xp, &o_p.xyz, &ray->tail_p); //calculates p(x, y, z)
			qdron_make(&qdrn, sqr);
			is_in_sqr(&qdrn,sqr);
		}
	}
	if (qdrn.xp_in == '+'/* && t < ray->dist*/ && ray->sgm == 0 && ray->dist > qdrn.t)
	{
		ray->dist = qdrn.t;
		ray->obj = 'q';
		ray->nrst = lscn->n_sqr;
		v_copy(&ray->vctr[0], &o_p);
		p_copy(&ray->hit_p, &qdrn.xp);
	}
	is_in_shdw(&qdrn, sqr, ray);
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