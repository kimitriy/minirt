/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lookat_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:44:31 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 20:20:41 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cnvrse_sqr(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_sqr	*sqr;
	t_sqr	*lsqr;

	nscn->n_sqr = nscn->frst_sqr;
	while (lscn->n_cntr.sqr < nscn->n_cntr.sqr)
	{
		make_t_sqr(lscn);
		if (lscn->n_cntr.sqr == 0)
			lscn->frst_sqr = lscn->n_sqr;
		if (lscn->n_sqr->next != NULL)
			lscn->n_sqr = lscn->n_sqr->next;
		sqr = nscn->n_sqr->content;
		lsqr = lscn->n_sqr->content;
		if (v_are_collinear(&sqr->v, &sqr->v_tmp) == 1)
			v_tmp_make(&sqr->v, &sqr->v_tmp, lookat);
		lsqr->side = sqr->side;
		color_copy(&lsqr->trgb, &sqr->trgb);
		mtrx4_x_point(&lsqr->p, &lookat->m, &sqr->p);
		mtrx4_x_vctr(&lsqr->v, &lookat->m, &sqr->v.nxyz);
		mtrx4_x_vctr(&lsqr->v_tmp, &lookat->m, &sqr->v_tmp.nxyz);
		if (nscn->n_sqr->next != NULL)
			nscn->n_sqr = nscn->n_sqr->next;
		lscn->n_cntr.sqr++;
	}
}

void	cnvrse_trngl(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_trngl	*trngl;
	t_trngl	*ltrngl;

	nscn->n_trngl = nscn->frst_trngl;
	while (lscn->n_cntr.trngl < nscn->n_cntr.trngl)
	{
		make_t_trngl(lscn);
		if (lscn->n_cntr.trngl == 0)
			lscn->frst_trngl = lscn->n_trngl;
		if (lscn->n_trngl->next != NULL)
			lscn->n_trngl = lscn->n_trngl->next;
		trngl = nscn->n_trngl->content;
		ltrngl = lscn->n_trngl->content;
		color_copy(&ltrngl->trgb, &trngl->trgb);
		mtrx4_x_point(&ltrngl->p1, &lookat->m, &trngl->p1);
		mtrx4_x_point(&ltrngl->p2, &lookat->m, &trngl->p2);
		mtrx4_x_point(&ltrngl->p3, &lookat->m, &trngl->p3);
		mtrx4_x_vctr(&ltrngl->n, &lookat->m, &trngl->n.nxyz);
		v_fill(&ltrngl->n);
		if (nscn->n_trngl->next != NULL)
			nscn->n_trngl = nscn->n_trngl->next;
		lscn->n_cntr.trngl++;
	}
}

void	cnvrse2local(t_scn *lscn, t_scn *nscn)
{
	t_cam		*cam;
	t_look_at	lookat;

	nscn->n_cam = nscn->frst_cam;
	cam = nscn->n_cam->content;
	look_at_mtrx(&lookat, &cam->v, &cam->p);
	lscn->n_rsltn = nscn->n_rsltn;
	lscn->n_ambnt = nscn->n_ambnt;
	get_cam_fov(nscn, lscn);
	cnvrse_lght(nscn, lscn, &lookat);
	cnvrse_pln(nscn, lscn, &lookat);
	cnvrse_sphr(nscn, lscn, &lookat);
	cnvrse_cyl(nscn, lscn, &lookat);
	cnvrse_sqr(nscn, lscn, &lookat);
	cnvrse_trngl(nscn, lscn, &lookat);
}

void	lookat_node(t_scn *nscn)
{
	t_scn	*lscn;

	lscn = make_t_scn(nscn->save);
	if (nscn->n_cntr.cam > 0)
		cnvrse2local(lscn, nscn);
	rays_node(lscn, nscn);
}
