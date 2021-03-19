/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:48:02 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 22:46:10 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	pln_calc(t_cylon *cln)
{
	t_plnx		plnx;
	t_vctr		tmp;

	plnx_null(&plnx);
	plnx = pln_equation(&cln->pln.p, &cln->o, &cln->pln.v, &cln->v_d);
	if (plnx.t != INFINITY && plnx.t > 0)
	{
		v_n_prdct(&cln->v_d.xyz, &cln->v_d.nxyz, plnx.t);
		v_fill(&cln->v_d);
		p_calc(&cln->p, &cln->v_d.xyz, &cln->o);
		v_make(&cln->v_p_c, &cln->p, &cln->pln.p);
	}
	p_copy(&cln->o_p, &plnx.o);
	v_make(&cln->v_o_c, &cln->o_p, &cln->pln.p);
	v_copy(&tmp, &plnx.orth);
	plnx_null(&plnx);
	plnx = pln_equation(&cln->pln.p, &cln->d, &cln->pln.v, &tmp);
	p_copy(&cln->d_p, &plnx.o);
	v_make(&cln->v_od, &cln->o_p, &cln->d_p);
}

void	cln_angles(t_cylon *cln)
{
	float tmp;

	cln->angle = v_angle(&cln->v_d, &cln->v_o_c) * 180 / M_PI;
	tmp = v_angle(&cln->v_d, &cln->pln.v);
	cln->sin_alpha = sinf(tmp);
}

void	ch_calc(t_cylon *cln, t_look_at *lkt)
{
	float	tmp;

	cylon_cnvrse(cln, lkt);
	tmp = v2d_pd_prdct(&cln->v_od_nb, &cln->v_oc_nb);
	cln->ch_p = fabsf(tmp / cln->v_od_nb.lngth);
}

void	calc_nrml_cyl(t_cylon *cln, t_cyl *cyl)
{
	t_vctr	cxp;
	t_vctr	cm;
	float	tmp;
	float	r;

	r = cyl->d / 2;
	v_null(&cxp);
	v_null(&cm);
	if (cln->t1 != INFINITY && cln->t1 > 0 && cln->t1 <= cln->t2)
		v_make(&cxp, &cln->pln.p, &cln->xp1);
	else if (cln->t2 != INFINITY && cln->t2 > 0 && cln->t1 > cln->t2)
		v_make(&cxp, &cln->pln.p, &cln->xp2);
	tmp = sqrt(powf(cxp.lngth, 2) - powf(r, 2));
	v_n_prdct(&cm.xyz, &cyl->v.nxyz, tmp);
	v_fill(&cm);
	v_sbtrct(&cyl->n.xyz, &cxp.xyz, &cm.xyz);
	v_fill(&cyl->n);
}

void	xp_cyl(t_cylon *cln)
{
	if (cln->t1 != INFINITY)
	{
		v_n_prdct(&cln->v_oxp1.xyz, &cln->v_d.nxyz, cln->t1);
		v_fill(&cln->v_oxp1);
		p_calc(&cln->xp1, &cln->v_oxp1.xyz, &cln->o);
	}
	if (cln->t2 != INFINITY)
	{
		v_n_prdct(&cln->v_oxp2.xyz, &cln->v_d.nxyz, cln->t2);
		v_fill(&cln->v_oxp2);
		p_calc(&cln->xp2, &cln->v_oxp2.xyz, &cln->o);
	}
}
