/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_pln_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:38:26 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 23:21:30 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	pln_null(t_pln *pln)
{
	p_make(&pln->p, 0, 0, 0);
	v_null(&pln->v);
	color_null(&pln->trgb);
	pln->nxt = NULL;
}

void	plnx_null(t_plnx *plnx)
{
	p_make(&plnx->o, 0, 0, 0);
	v_null(&plnx->orth);
	plnx->t = INFINITY;
}

void	pln_make(t_pln *pln, t_point *p, t_vctr *v)
{
	pln_null(pln);
	p_copy(&pln->p, p);
	v_copy(&pln->v, v);
}

t_plnx	pln_equation(t_point *p, t_point *r_orgn, t_vctr *nrml, t_vctr *ray)
{
	t_pln	pln;
	t_plnx	plnx;
	float	tmp1;
	float	tmp2;

	pln_make(&pln, p, nrml);
	plnx_null(&plnx);
	p2pln_prjctn(&plnx, &pln, r_orgn);
	tmp1 = v_d_prdct(&plnx.orth.xyz, &nrml->nxyz);
	tmp2 = v_d_prdct(&ray->nxyz, &nrml->nxyz);
	if (tmp2 != 0)
		plnx.t = 0.99999 * tmp1 / tmp2;
	return (plnx);
}
