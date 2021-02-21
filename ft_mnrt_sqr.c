/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sqr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:46:58 by rburton           #+#    #+#             */
/*   Updated: 2021/02/20 23:39:57 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	qdron_null(t_qdron *qdrn)
{
	qdrn->xp_in = '\0';
	qdrn->alpha = 0;
	qdrn->x = 0;
	qdrn->y = 0;
	p_make(&qdrn->xp, 0, 0, 0);
	v_null(&qdrn->vTMP);
	v_null(&qdrn->vR);
	v_null(&qdrn->vUP);
	v_null(&qdrn->vPXP);
}

void	qdron_make(t_qdron *qdrn, t_sqr *sqr)
{
	v_tmp_make(&qdrn->vTMP, &sqr->v); //creates vTMP
	v_crss_prdct(&qdrn->vR.xyz, &sqr->v.nxyz, &qdrn->vTMP.nxyz); //creates vR
	v_fill(&qdrn->vR);
	v_crss_prdct(&qdrn->vUP.xyz, &qdrn->vR.nxyz, &sqr->v.nxyz); //creates vUP
	v_fill(&qdrn->vUP);
	v_make(&qdrn->vPXP, &sqr->p, &qdrn->xp); //creates vCA
	qdrn->alpha = v_d_prdct(&qdrn->vR.nxyz, &qdrn->vPXP.xyz);
	qdrn->x = qdrn->vPXP.lngth * qdrn->alpha;
	qdrn->y = sinf(qdrn->alpha) * qdrn->vPXP.lngth;
}

void	is_in_sqr(t_qdron *qdrn,t_sqr *sqr)
{
	if (fabsf(qdrn->x) <= sqr->side / 2 && fabsf(qdrn->y) <= sqr->side / 2)
		qdrn->xp_in = '+';
}

void	sqr_intrsct(t_scn *lscn, t_sqr *sqr, t_ray *ray)
{
	t_vctr		o_p; //vctr from ray origin to the pln that is collinear to ray->vctr[0] and reaches p
	float		t;	//distance between the ray origin point and the intersection piont
	t_qdron		qdrn;

	qdron_null(&qdrn);
	nrml_sqr(sqr, ray);
	t = pln_equation(&sqr->p, &ray->tail_p, &sqr->v, &ray->vctr[ray->sgm]);
	if (fabsf(t) < INFINITY && t > 0.00006)
	{
		v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, t); //calculates vctr from ray origin point to the intrsct_p
		v_fill(&o_p);
		p_calc(&qdrn.xp, &o_p, &ray->tail_p); //calculates p(x, y, z)
		qdron_make(&qdrn, sqr);
		is_in_sqr(&qdrn,sqr);
	}
	if (qdrn.xp_in == '+' && t < ray->dist && ray->sgm == 0)
	{
		ray->dist = t;
		ray->obj = 'q';
		ray->nrst = lscn->n_sqr;
		v_copy(&ray->vctr[0], &o_p);
		p_copy(&ray->hit_p, &qdrn.xp);
	}
	if (qdrn.xp_in == '+' && ray->sgm == 1 && t > 0 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
		ray->shdw = 'y';
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