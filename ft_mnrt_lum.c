/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:16:42 by rburton           #+#    #+#             */
/*   Updated: 2021/02/28 22:05:36 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

//La
void	l_ambnt(t_lum *lum)
{
	const float pi = 3.141593;
	float		beta;

	beta = v_angle(&lum->op, &lum->nrml) * 180 / pi;
	lum->angl = 180 - beta;
	lum->ka = (lum->angl >= 0 && lum->angl < 90) ? cos(lum->angl * pi / 180) : 0;
	lum->la = lum->alvl * lum->ka;
}

//Ld
void	l_dffse(t_lum *lum)
{
    float	fade;
	float	mx;
	
	lum->kd = 30;
	fade = lum->lvl / powf(lum->dst, 2);
	mx = max_2floats(0, v_d_prdct(&lum->ldir.nxyz, &lum->nrml.nxyz));
	lum->ld = lum->kd * fade * mx;
}

//Ls
void	l_spclr(t_lum *lum)
{
	float	fade;
	float	mx;

	lum->ks = 30;
	lum->p = 64;
	fade = lum->lvl / powf(lum->dst, 2);
	mx = max_2floats(0, v_d_prdct(&lum->nrml.nxyz, &lum->hvctr.nxyz));
	lum->ls = lum->ks * fade * powf(mx, lum->p);
}

void	l_all(t_scn *lscn, t_lum *lum)
{
	if (lum->shdw == 'y' || lscn->n_cntr.lght == 0)
	{
		l_ambnt(lum);
		lum->ld = 0;
		lum->ls = 0;
	}
	else
	{	
		l_ambnt(lum);
		l_dffse(lum);
		l_spclr(lum);
	}
	lum->l = lum->la + lum->ld + lum->ls;
	lum->l = lum->l >= 1 ? 1 : lum->l;
}

void	make_lum(t_lum *lum, t_scn *lscn, t_lght *lght, t_ray *ray)
{
	t_vctr  opposite_op;

	lum->shdw = ray->shdw;
	lum->alvl = lscn->n_ambnt.lvl;
	lum->lvl = lght->lvl;
	color_copy(&lum->l_trgb, &lght->trgb);
	v_copy(&lum->op, &ray->vctr[0]); //op vctr which is already calculated and stored in the ray struct
	v_copy(&lum->ldir, &ray->vctr[1]);
    lum->dst = lum->ldir.lngth;
    v_null(&opposite_op);
	opposite_op.nxyz.x = (-1) * lum->op.nxyz.x;
    opposite_op.nxyz.y = (-1) * lum->op.nxyz.y;
    opposite_op.nxyz.z = (-1) * lum->op.nxyz.z;
    v_fill(&opposite_op);
	v_null(&lum->hvctr);
    v_sum(&lum->hvctr.xyz, &lum->ldir.nxyz, &opposite_op.nxyz);
    v_fill(&lum->hvctr);
}

void    lum_sphr(t_scn *lscn, t_lght *lght, t_ray *ray)
{
    t_lum   lum;
	t_sphr	*sphr;

	sphr = ray->nrst->content;
    make_lum(&lum, lscn, lght, ray);
	nrml_sphr(&lum.nrml, ray, sphr); //makes nrml vctr
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &sphr->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_pln(t_scn *lscn, t_lght *lght, t_ray *ray)
{
    t_lum   lum;
	t_pln	*pln;

	pln = ray->nrst->content;
	v_copy(&lum.nrml, &pln->v);
	make_lum(&lum, lscn, lght, ray);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &pln->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_trngl(t_scn *lscn, t_lght *lght, t_ray *ray)
{
    t_lum   lum;
	t_trngl	*trngl;

	trngl = ray->nrst->content;
	ray->sgm = 0;
	nrml_trngl(trngl, ray);
	v_copy(&lum.nrml, &trngl->n);
	v_fill(&lum.nrml);
	make_lum(&lum, lscn, lght, ray);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &trngl->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_sqr(t_scn *lscn, t_lght *lght, t_ray *ray)
{
    t_lum   lum;
	t_sqr	*sqr;

	sqr = ray->nrst->content;
	ray->sgm = 0;
	nrml_sqr(sqr, ray);
	v_copy(&lum.nrml, &sqr->v);
	v_fill(&lum.nrml);
	make_lum(&lum, lscn, lght, ray);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &sqr->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_cyl(t_scn *lscn, t_lght *lght, t_ray *ray)
{
    t_lum   lum;
	t_cyl	*cyl;

	cyl = ray->nrst->content;
	ray->sgm = 0;
	nrml_cyl(cyl, ray);

	v_copy(&lum.nrml, &cyl->n1);
	v_fill(&lum.nrml);
	make_lum(&lum, lscn, lght, ray);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &cyl->trgb);
	color_node(lscn, ray, &lum);
}

/*
obj types:
p - pln;
s - sphr;
c - cyl;
q - sqr;
t - trngl;
*/

void	lum_node(t_scn *lscn, t_lght *lght, t_ray *ray)
{

	if (ray->obj == 's')
		lum_sphr(lscn, lght, ray);
	if (ray->obj == 'p')
		lum_pln(lscn, lght, ray);
	if (ray->obj == 't')
		lum_trngl(lscn, lght, ray);
	if (ray->obj == 'q')
		lum_sqr(lscn, lght, ray);
	if (ray->obj == 'c')
		lum_cyl(lscn, lght, ray);
	
}