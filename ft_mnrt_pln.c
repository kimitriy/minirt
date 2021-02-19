/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_pln.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:38:26 by rburton           #+#    #+#             */
/*   Updated: 2021/02/19 23:40:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	pln_equation(t_point *p, t_point *r_orgn, t_vctr *nrml, t_vctr *ray)
{
	float	dist;
	t_vctr	o_p0; //vctr from .o (tail point) to the pln
	t_point	p0;	//point on the pln, projection of tail point to this pln
	float tmp1;
	float tmp2;
	float t;

	dist = (p->x - r_orgn->x) * nrml->nxyz.x + (p->y - r_orgn->y) * nrml->nxyz.y + (p->z - r_orgn->z) * nrml->nxyz.z; //1
	dist = dist < 0 ? dist * (-1) : dist; //2
	v_n_prdct(&o_p0.xyz, &nrml->nxyz, dist); //3
	v_n_prdct(&o_p0.xyz, &o_p0.xyz, -1); //3 change the sign (direction)
	v_fill(&o_p0);
	p_calc(&p0, &o_p0, r_orgn); //4
	tmp1 = v_d_prdct(&o_p0.xyz, &nrml->nxyz); //6, 7
	tmp2 = v_d_prdct(&ray->nxyz, &nrml->nxyz); //8
	t = 1.00001 * tmp1 / tmp2; //9
	return (t);
}

void	pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray)
{
	float	t;
	t_vctr	*orth;

	nrml_pln(pln, ray);
	t = pln_equation(&pln->p, &ray->tail_p, &pln->v, &ray->vctr[ray->sgm]);
	
	if (t > 0 && t < ray->dist && ray->sgm == 0)
	{
		ray->dist = t;
		ray->obj = 'p';
		ray->nrst = lscn->n_pln;
		v_n_prdct(&ray->vctr[0].xyz, &ray->vctr[ray->sgm].nxyz, ray->dist);
		v_fill(&ray->vctr[0]);
		p_calc(&ray->hit_p, &ray->vctr[0], &ray->tail_p);
	}
	if (ray->sgm == 1 && t > 0.0003 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
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