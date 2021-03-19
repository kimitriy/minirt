/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sqr_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:46:58 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 17:36:47 by rburton          ###   ########.fr       */
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
	v_null(&qdrn->v_tmp);
	v_null(&qdrn->v_r);
	v_null(&qdrn->v_up);
	v_null(&qdrn->v_cxp);
}

void	qdron_make(t_qdron *qdrn, t_sqr *sqr)
{
	t_look_at	lkt;

	v_copy(&lkt.v_tmp, &sqr->v_tmp);
	lkt.tmp = '+';
	look_at_mtrx(&lkt, &sqr->v, &sqr->p);
	v_copy(&qdrn->v_tmp, &lkt.v_tmp);
	v_copy(&qdrn->v_r, &lkt.v_r);
	v_copy(&qdrn->v_up, &lkt.v_up);
	v_make(&qdrn->v_cxp, &sqr->p, &qdrn->xp);
	qdrn->alpha = v_angle(&qdrn->v_r, &qdrn->v_cxp);
	qdrn->x = qdrn->v_cxp.lngth * cosf(qdrn->alpha);
	qdrn->y = qdrn->v_cxp.lngth * sinf(qdrn->alpha);
	is_in_sqr(qdrn, sqr);
}

void	is_in_sqr(t_qdron *qdrn, t_sqr *sqr)
{
	if (fabsf(qdrn->x) <= sqr->side / 2 && fabsf(qdrn->y) <= sqr->side / 2)
		qdrn->xp_in = '+';
}

void	is_in_shdw(t_qdron *qdrn, t_sqr *sqr, t_ray *ray)
{
	if (qdrn->xp_in == '+' && ray->sgm == 1 && qdrn->t < ray->vctr[1].lngth)
		ray->shdw = 'y';
	else if (qdrn->xp_in == '+' && ray->sgm == 1 &&
		v_d_prdct(&sqr->v.nxyz, &ray->vctr[1].nxyz) < 0)
		ray->shdw = 'y';
}
