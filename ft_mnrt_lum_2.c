/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lum_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:59:30 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 13:00:39 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	make_lum(t_lum *lum, t_scn *lscn, t_lght *lght, t_ray *ray)
{
	t_vctr	opposite_op;

	lum->shdw = ray->shdw;
	lum->alvl = lscn->n_ambnt.lvl;
	lum->lvl = lght->lvl;
	color_copy(&lum->l_trgb, &lght->trgb);
	v_copy(&lum->op, &ray->vctr[0]);
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

void	lum_sphr(t_scn *lscn, t_lght *lght, t_ray *ray)
{
	t_lum	lum;
	t_sphr	*sphr;

	sphr = ray->nrst->content;
	make_lum(&lum, lscn, lght, ray);
	nrml_sphr(&lum.nrml, ray, sphr);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &sphr->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_pln(t_scn *lscn, t_lght *lght, t_ray *ray)
{
	t_lum	lum;
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
	t_lum	lum;
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
