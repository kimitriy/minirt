/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_pln.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:38:26 by rburton           #+#    #+#             */
/*   Updated: 2021/03/17 02:31:47 by rburton          ###   ########.fr       */
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
	p_make(&plnx->_o, 0, 0, 0);
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
	float tmp1;
	float tmp2;

	pln_make(&pln, p, nrml);
	plnx_null(&plnx);
	p2pln_prjctn(&plnx, &pln, r_orgn);
	tmp1 = v_d_prdct(&plnx.orth.xyz, &nrml->nxyz); //6, 7
	tmp2 = v_d_prdct(&ray->nxyz, &nrml->nxyz); //8
	if (tmp2 != 0)
		plnx.t = 0.99999 * tmp1 / tmp2; //9
	return (plnx);
}

void	pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray)
{
	float	t;

	nrml_pln(pln, ray);
	t = pln_equation(&pln->p, &ray->tail_p, &pln->v, &ray->vctr[ray->sgm]).t;
	
	if (t > 0.00001 && t < ray->dist && ray->sgm == 0)
	{
		ray->dist = t;
		ray->obj = 'p';
		ray->nrst = lscn->n_pln;
		v_n_prdct(&ray->vctr[0].xyz, &ray->vctr[ray->sgm].nxyz, ray->dist);
		v_fill(&ray->vctr[0]);
		p_calc(&ray->hit_p, &ray->vctr[0].xyz, &ray->tail_p);
	}
	if (ray->sgm == 1 && t > 0 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
		ray->shdw = 'y';
}

void 	check_plns(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_pln	*pln;

	i = 0;
	lscn->n_pln = lscn->frst_pln;
	while (i < lscn->n_cntr.pln)
	{
		pln = lscn->n_pln->content;
		pln->v.xyz.x = 0;
		pln->v.xyz.y = 0;
		pln->v.xyz.z = 0;
		v_fill(&pln->v);
		pln_intrsct(lscn, pln, ray);
		if (lscn->n_pln->next != NULL)
			lscn->n_pln = lscn->n_pln->next;
		i++;
	}
}