/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/31 22:41:12 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	q_equation(float *dscr, float a, float b, float c)
{
	float	r1;
	float	r2;
	float	root;

	*dscr = powf(b, 2) - 4 * a * c;
	if (dscr == 0)
		root = b / (2 * a);
	else if (dscr > 0)
	{
		r1 = (b + sqrtf(*dscr)) / (2 * a);
		r2 = (b - sqrtf(*dscr)) / (2 * a);
		if (r1 < r2)
			root = r1;
		else
			root = r2;
	}
	return (root);
}

void	sphr_intrsct(t_scn *lscn, t_sphr *sphr, t_ray *ray)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	a;
	float	b;
	float	c;
	float	dscr;
	float	root;
	
	v_make(&oc, &ray->tail_p, &sphr->p);
	//v_fill(&oc);
	a = v_d_prdct(&ray->vctr[ray->sgm].nxyz,&ray->vctr[ray->sgm].nxyz);
	b = 2 * v_d_prdct(&oc.xyz, &ray->vctr[ray->sgm].nxyz);
	c = v_d_prdct(&oc.xyz, &oc.xyz) - powf(sphr->d, 2);
	root = q_equation(&dscr, a, b, c);
	if (dscr >= 0 && root < ray->dist[ray->sgm] && root > 0)
	{
		ray->dist[ray->sgm] = root;
		ray->obj = 's';
		ray->nrst = lscn->n_sphr;
		v_n_prdct(&ray->vctr[ray->sgm].xyz, &ray->vctr[ray->sgm].nxyz, ray->dist[ray->sgm]); //makes a ray from the cam point to the intersection point
		v_fill(&ray->vctr[ray->sgm]);
		p_calc(&ray->hit_p[ray->sgm], &ray->vctr[ray->sgm], &ray->tail_p); //calculates the hit point
	}
}

void	pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the projection of the O point on the pln

	//t = - oc * vN / vD * vN;
	//vD - unit vctr of the ray, it is given
	//vN - unit nrml vctr of the pln, it is given
	//oc - vctr from O(0,0,0) to pln, it is orthogonal to the pln and required to calculate
	//to calc oc vctr we need pln equation:

	float	dst; //it is the solution and it is the distance from arbitrary point to the pln
	t_point	ap; //arbitrary point
	p_make(&ap, 0, 0, 0); //which is the O(0,0,0) point in this particular case

	dst =  pln->v.nxyz.x * (pln->p.x - ap.x) + pln->v.nxyz.y * (pln->p.y - ap.y) + pln->v.nxyz.z * (pln->p.z - ap.z);

	v_n_prdct(&oc.xyz, &pln->v.nxyz, dst); //calc oc vctr
	v_fill(&oc);
	
	float 	t; //point of intersection
	float	tmp1;
	float	tmp2;
	tmp1 = v_d_prdct(&oc.xyz, &pln->v.nxyz);
	tmp2 = v_d_prdct(&ray->vctr->nxyz, &pln->v.nxyz);
	t = v_d_prdct(&oc.xyz, &pln->v.nxyz) / v_d_prdct(&ray->vctr->nxyz, &pln->v.nxyz); //deleted -1
	if (t > 0 && t < ray->dist[ray->sgm])
	{
		ray->dist[ray->sgm] = t;
		ray->obj = 'p';
		ray->nrst = lscn->n_pln;
		v_n_prdct(&ray->vctr[ray->sgm].xyz, &ray->vctr[ray->sgm].nxyz, ray->dist[ray->sgm]);
		v_fill(&ray->vctr[ray->sgm]);
		p_calc(&ray->hit_p[ray->sgm], &ray->vctr[ray->sgm], &ray->tail_p);
	}
}

void 	check_sphrs(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_sphr	*sphr;

	i = 0;
	lscn->n_sphr = lscn->frst_sphr;
	while (i < lscn->n_cntr.sphr)
	{
		sphr = lscn->n_sphr->content;
		sphr_intrsct(lscn, sphr, ray);
		if (lscn->n_sphr->next != NULL)
			lscn->n_sphr = lscn->n_sphr->next;
		i++;
	}
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
		pln_intrsct(lscn, pln, ray);
		if (lscn->n_pln->next != NULL)
			lscn->n_pln = lscn->n_pln->next;
		i++;
	}
}

void	intrsct_node(t_scn *lscn, t_ray *ray)
{
	t_lght	*lght;

	check_sphrs(lscn, ray);
	check_plns(lscn, ray);
	// check_cyls(lscn, ray);
	// check_sqrs(lscn, ray);
	// check_trngls(lscn, ray);
	if (ray->dist[0] < INFINITY && ray->sgm == 0)
	{
		lght = lscn->n_lght->content;
		ray->tail_p = ray->hit_p[ray->sgm];
		ray->head_p = lght->p;
		ray->sgm++;
		trace_ray(lscn, ray);
	}
	if (ray->dist[1] < INFINITY && ray->sgm == 1)
	{
		ray->shdw = 'y';
		lum_node(lscn, ray);
	}
	else if (ray->dist[0] < INFINITY && ray->sgm == 1)
		lum_node(lscn, ray);
}