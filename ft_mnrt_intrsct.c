/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/02/12 18:32:20 by rburton          ###   ########.fr       */
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
		if (r1 > 0 && r2 > 0)
		{
			if (r1 < r2)
				root = r1;
			else
				root = r2;
		}
		else if (r1 > 0 && r2 < 0)
			root = r1;
		else if (r2 > 0 && r1 < 0)
			root = r2;
	}
	return (root);
}

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

void	sphr_intrsct(t_scn *lscn, t_sphr *sphr, t_ray *ray)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	a;
	float	b;
	float	c;
	float	dscr;
	float	root;
	
	v_null(&oc);
	v_make(&oc, &ray->tail_p, &sphr->p);
	a = v_d_prdct(&ray->vctr[ray->sgm].nxyz,&ray->vctr[ray->sgm].nxyz);
	b = 2 * v_d_prdct(&oc.xyz, &ray->vctr[ray->sgm].nxyz);
	c = v_d_prdct(&oc.xyz, &oc.xyz) - powf(sphr->d / 2, 2);
	root = q_equation(&dscr, a, b, c) * 1.00001;
	if (dscr >= 0 && root < ray->dist && root > 0 && ray->sgm == 0)
	{
		ray->dist = root;
		ray->obj = 's';
		ray->nrst = lscn->n_sphr;
		v_n_prdct(&ray->vctr[0].xyz, &ray->vctr[0].nxyz, ray->dist); //makes a ray from the cam point to the intersection point
		v_fill(&ray->vctr[0]);
		p_calc(&ray->hit_p, &ray->vctr[0], &ray->tail_p); //calculates the hit point
	}
	if (ray->sgm == 1 && dscr >= 0 && root > 0.01 && root < ray->vctr[1].lngth && ray->shdw != 'y')
		ray->shdw = 'y';
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

void	plgn_null(t_polygon *plgn)
{
	plgn->f = '\0';
	plgn->p_in = '\0';
	p_make(&plgn->p, 0, 0, 0);
	p_make(&plgn->a, 0, 0, 0);
	p_make(&plgn->b, 0, 0, 0);
	p_make(&plgn->c, 0, 0, 0);
	p_make(&plgn->d, 0, 0, 0);
	v_null(&plgn->a_b);
	v_null(&plgn->b_c);
	v_null(&plgn->c_d);
	v_null(&plgn->cd_a);
	v_null(&plgn->p_a);
	v_null(&plgn->p_b);
	v_null(&plgn->p_c);
	v_null(&plgn->p_d);
	plgn->prmtr = 0;
	plgn->prmtr1 = 0;
	plgn->prmtr2 = 0;
	plgn->prmtr3 = 0;
	plgn->prmtr4 = 0;
	plgn->area = 0;
	plgn->area1 = 0;
	plgn->area2 = 0;
	plgn->area3 = 0;
	plgn->area4 = 0;
}

void	plgn_prmtr(t_polygon *plgn)
{
	plgn->prmtr = (plgn->a_b.lngth + plgn->b_c.lngth + plgn->cd_a.lngth) / 2;
	plgn->prmtr1 = (plgn->p_a.lngth + plgn->a_b.lngth + plgn->p_b.lngth) / 2;
	plgn->prmtr2 = (plgn->p_b.lngth + plgn->b_c.lngth + plgn->p_c.lngth) / 2;
	plgn->prmtr3 = (plgn->p_c.lngth + plgn->cd_a.lngth + plgn->p_a.lngth) / 2;
}

void	plgn_area(t_polygon *plgn)
{
	plgn->area = sqrtf(plgn->prmtr * (plgn->prmtr - plgn->a_b.lngth) * (plgn->prmtr - plgn->b_c.lngth) * (plgn->prmtr - plgn->cd_a.lngth));
	plgn->area1 = sqrtf(plgn->prmtr1 * (plgn->prmtr1 - plgn->p_a.lngth) * (plgn->prmtr1 - plgn->a_b.lngth) * (plgn->prmtr1 - plgn->p_b.lngth));
	plgn->area2 = sqrtf(plgn->prmtr2 * (plgn->prmtr2 - plgn->p_b.lngth) * (plgn->prmtr2 - plgn->b_c.lngth) * (plgn->prmtr2 - plgn->p_c.lngth));
	plgn->area3 = sqrtf(plgn->prmtr3 * (plgn->prmtr3 - plgn->p_c.lngth) * (plgn->prmtr3 - plgn->cd_a.lngth) * (plgn->prmtr3 - plgn->p_a.lngth));
}

void	is_in_trngl(t_trngl *trngl)
{
	if (trngl->plgn.area >= 0.9999 * (trngl->plgn.area1 + trngl->plgn.area2 + trngl->plgn.area3))
		trngl->plgn.p_in = '+';
}

void	plgn_make(t_trngl *trngl, t_ray *ray)
{
	if (trngl->plgn.f != 'f')
	{
		p_copy(&trngl->plgn.a, &trngl->p1);
		p_copy(&trngl->plgn.b, &trngl->p2);
		p_copy(&trngl->plgn.c, &trngl->p3);
		v_make(&trngl->plgn.cd_a, &trngl->plgn.c, &trngl->plgn.a);
		v_make(&trngl->plgn.a_b, &trngl->plgn.a, &trngl->plgn.b);
		v_make(&trngl->plgn.b_c, &trngl->plgn.b, &trngl->plgn.c);
		// nrml_trngl(plgn, trngl, ray, '\0'); //1, 2
		trngl->plgn.f = 'f';
	}
	else if (trngl->plgn.f == 'f')
	{
		v_make(&trngl->plgn.p_a, &trngl->plgn.p, &trngl->plgn.a);
		v_make(&trngl->plgn.p_b, &trngl->plgn.p, &trngl->plgn.b);
		v_make(&trngl->plgn.p_c, &trngl->plgn.p, &trngl->plgn.c);
		plgn_prmtr(&trngl->plgn);
		plgn_area(&trngl->plgn);
		is_in_trngl(trngl);
	}
}

void	trngl_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray)
{
	//t_polygon	plgn;
	t_vctr		o_p; //vctr from ray origin to the pln that is collinear to ray->vctr[0] and reaches p
	float		t;
	
	plgn_null(&trngl->plgn);
	plgn_make(trngl, ray);
	nrml_trngl(trngl, ray);
	t = pln_equation(&trngl->p1, &ray->tail_p, &trngl->n, &ray->vctr[ray->sgm]); //3, 4
	if (fabsf(t) < INFINITY && t > 0.00006)
	{
		// t = ray->sgm == 1 ? -t : t;
		v_n_prdct(&o_p.xyz, &ray->vctr[ray->sgm].nxyz, t); //calculates vctr from ray origin point to p
		v_fill(&o_p);
		p_calc(&trngl->plgn.p, &o_p, &ray->tail_p); //calculates p(x, y, z)
		plgn_make(trngl, ray);
	}
	if (trngl->plgn.p_in == '+' && t > 0 && t < ray->dist && ray->sgm == 0)
	{
		ray->dist = t;
		ray->obj = 't';
		ray->nrst = lscn->n_trngl;
		v_copy(&ray->vctr[0], &o_p);
		p_copy(&ray->hit_p, &trngl->plgn.p);
	}
	if (trngl->plgn.p_in == '+' && ray->sgm == 1 && t > 0 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
		ray->shdw = 'y';
	
	// if (ray->sgm == 1 && t > 0.0003 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
}

// void	sqr_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray)
// {
	
// 	if (plgn.area >= 0.9999 * (plgn.area1 + plgn.area2 + plgn.area3) && t < ray->dist && ray->sgm == 0)
// 	{
// 		ray->dist = t;
// 		ray->obj = 't';
// 		ray->nrst = lscn->n_trngl;
// 		v_copy(&ray->vctr[0], &o_p);
// 		p_copy(&ray->hit_p, &plgn.p);
// 	}
// 	if (plgn.area >= 0.9999 * (plgn.area1 + plgn.area2 + plgn.area3) && ray->sgm == 1 && t > 0.00004 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
// 		ray->shdw = 'y';
// }

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

void 	check_trngls(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_trngl	*trngl;

	i = 0;
	lscn->n_trngl = lscn->frst_trngl;
	while (i < lscn->n_cntr.trngl)
	{
		trngl = lscn->n_trngl->content;
		trngl_intrsct(lscn, trngl, ray);
		if (lscn->n_trngl->next != NULL)
			lscn->n_trngl = lscn->n_trngl->next;
		i++;
	}
}

// void 	check_sqrs(t_scn *lscn, t_ray *ray)
// {
// 	int		i;
// 	t_trngl	*sqr;

// 	i = 0;
// 	lscn->n_sqr = lscn->frst_sqr;
// 	while (i < lscn->n_cntr.sqr)
// 	{
// 		sqr = lscn->n_sqr->content;
// 		sqr_intrsct(lscn, sqr, ray);
// 		if (lscn->n_sqr->next != NULL)
// 			lscn->n_sqr = lscn->n_sqr->next;
// 		i++;
// 	}
// }

void	check_objcts(t_scn *lscn, t_ray *ray)
{	
	check_sphrs(lscn, ray);
	check_trngls(lscn, ray);
	// check_sqrs(lscn, ray);
	// check_cyls(lscn, ray);
	check_plns(lscn, ray);
}

void	check_lghts(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_lght	*lght;
	
	lscn->n_lght = lscn->frst_lght;
	i = 0;
	color_null(&ray->p_trgb);
	while (i < lscn->n_cntr.lght)
	{
		lght = lscn->n_lght->content;
		if (ray->dist < INFINITY)
		{
			ray->tail_p = ray->hit_p;
			ray->head_p = lght->p;
			ray->sgm = 1;
			v_make(&ray->vctr[1], &ray->tail_p, &ray->head_p); //!!!
			check_objcts(lscn, ray);
		}
		if (ray->dist < INFINITY && ray->sgm > 0)
			lum_node(lscn, lght, ray);
		if (lscn->n_lght->next != NULL)
			lscn->n_lght = lscn->n_lght->next;
		ray->shdw = '\0';
		i++;
	}
	//ray->sgm = 0;
}

void	intrsct_node(t_scn *lscn, t_ray *ray)
{
	t_lght	nolght;

	check_objcts(lscn, ray);
	if (ray->dist < INFINITY && lscn->n_cntr.lght > 0)
		check_lghts(lscn, ray);
	else if (ray->dist < INFINITY && lscn->n_cntr.lght == 0)
	{
		t_lght_null(&nolght);
		lum_node(lscn, &nolght, ray);
	}
}