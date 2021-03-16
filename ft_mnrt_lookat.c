/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lookat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:11:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/17 01:15:50 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	null_lookat(t_look_at *lookat)
{
	if (lookat->tmp != '+')
		v_null(&lookat->v_tmp);
	v_null(&lookat->v_f);
	v_null(&lookat->v_r);
	v_null(&lookat->v_up);
}

void	v_tmp_make(t_vctr *vf, t_vctr *vtmp, t_look_at *lkt)
{
	if (lkt->tmp != '+')
	{
		vtmp->xyz.x = 0;
		if (vf->nxyz.y == 1)
		{
			vtmp->xyz.y = 0;
			vtmp->xyz.z = -1;
		}
		else if (vf->xyz.y == -1)
		{
			vtmp->xyz.y = 0;
			vtmp->xyz.z = 1;
		}
		else
		{
			vtmp->xyz.y = 1;
			vtmp->xyz.z = 0;
		}
	}
	v_fill(vtmp);
}

void	look_at_mtrx(t_look_at *lookat, t_vctr *vf, t_point *p)
{
	null_lookat(lookat);
	v_n_prdct(&lookat->v_f.xyz, &vf->nxyz, -1);
	v_fill(&lookat->v_f);
	v_tmp_make(&lookat->v_f, &lookat->v_tmp, lookat);
	v_crss_prdct(&lookat->v_r.xyz, &lookat->v_f.nxyz, &lookat->v_tmp.nxyz);
	v_fill(&lookat->v_r);
	v_crss_prdct(&lookat->v_up.xyz, &lookat->v_r.nxyz, &lookat->v_f.nxyz);
	v_fill(&lookat->v_up);
	lookat->m.m[0][0] = lookat->v_r.nxyz.x;
	lookat->m.m[0][1] = lookat->v_r.nxyz.y;
	lookat->m.m[0][2] = lookat->v_r.nxyz.z;
	lookat->m.m[0][3] = -v_x_point_prdct(&lookat->v_r.nxyz, p);
	lookat->m.m[1][0] = lookat->v_up.nxyz.x;
	lookat->m.m[1][1] = lookat->v_up.nxyz.y;
	lookat->m.m[1][2] = lookat->v_up.nxyz.z;
	lookat->m.m[1][3] = -v_x_point_prdct(&lookat->v_up.nxyz, p);
	lookat->m.m[2][0] = lookat->v_f.nxyz.x;
	lookat->m.m[2][1] = lookat->v_f.nxyz.y;
	lookat->m.m[2][2] = lookat->v_f.nxyz.z;
	lookat->m.m[2][3] = -v_x_point_prdct(&lookat->v_f.nxyz, p);
	lookat->m.m[3][0] = 0;
	lookat->m.m[3][1] = 0;
	lookat->m.m[3][2] = 0;
	lookat->m.m[3][3] = 1;
}

void	get_cam_fov(t_scn *nscn, t_scn *lscn)
{
	t_cam	*cam;
	t_cam	*lcam;

	make_t_cam(lscn);
	if (lscn->n_cntr.cam == 0)
		lscn->frst_cam = lscn->n_cam;
	if (lscn->n_cam->next != NULL)
		lscn->n_cam = lscn->n_cam->next;
	cam = nscn->n_cam->content;
	lcam = lscn->n_cam->content;
	lcam->fov = cam->fov;
	lscn->n_cntr.cam++;
}

void	cnvrse_lght(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_lght	*lght;
	t_lght	*llght;

	while (lscn->n_cntr.lght < nscn->n_cntr.lght)
	{
		make_t_lght(lscn);
		if (lscn->n_cntr.lght == 0)
			lscn->frst_lght = lscn->n_lght;
		if (lscn->n_lght->next != NULL)
			lscn->n_lght = lscn->n_lght->next;
		lght = nscn->n_lght->content;
		llght = lscn->n_lght->content;
		color_copy(&llght->trgb, &lght->trgb);
		llght->lvl = lght->lvl;
		mtrx4_x_point(&llght->p, &lookat->m, &lght->p);
		if (nscn->n_lght->next != NULL)
			nscn->n_lght = nscn->n_lght->next;
		lscn->n_cntr.lght++;
	}
}

void	cnvrse_pln(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_pln	*pln;
	t_pln	*lpln;

	nscn->n_pln = nscn->frst_pln;
	while (lscn->n_cntr.pln < nscn->n_cntr.pln)
	{
		make_t_pln(lscn);
		if (lscn->n_cntr.pln == 0)
			lscn->frst_pln = lscn->n_pln;
		if (lscn->n_pln->next != NULL)
			lscn->n_pln = lscn->n_pln->next;
		pln = nscn->n_pln->content;
		lpln = lscn->n_pln->content;
		color_copy(&lpln->trgb, &pln->trgb);
		mtrx4_x_point(&lpln->p, &lookat->m, &pln->p);
		mtrx4_x_vctr(&lpln->v, &lookat->m, &pln->v.nxyz);
		v_fill(&lpln->v);
		if (nscn->n_pln->next != NULL)
			nscn->n_pln = nscn->n_pln->next;
		lscn->n_cntr.pln++;
	}
}

void	cnvrse_sphr(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_sphr	*sphr;
	t_sphr	*lsphr;

	nscn->n_sphr = nscn->frst_sphr;
	while (lscn->n_cntr.sphr < nscn->n_cntr.sphr)
	{
		make_t_sphr(lscn);
		if (lscn->n_cntr.sphr == 0)
			lscn->frst_sphr = lscn->n_sphr;
		if (lscn->n_sphr->next != NULL)
			lscn->n_sphr = lscn->n_sphr->next;
		sphr = nscn->n_sphr->content;
		lsphr = lscn->n_sphr->content;
		lsphr->d = sphr->d;
		color_copy(&lsphr->trgb, &sphr->trgb);
		mtrx4_x_point(&lsphr->p, &lookat->m, &sphr->p);
		if (nscn->n_sphr->next != NULL)
			nscn->n_sphr = nscn->n_sphr->next;
		lscn->n_cntr.sphr++;
	}
}

void	cnvrse_cyl(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_cyl	*cyl;
	t_cyl	*lcyl;

	nscn->n_cyl = nscn->frst_cyl;
	while (lscn->n_cntr.cyl < nscn->n_cntr.cyl)
	{
		make_t_cyl(lscn);
		if (lscn->n_cntr.cyl == 0)
			lscn->frst_cyl = lscn->n_cyl;
		if (lscn->n_cyl->next != NULL)
			lscn->n_cyl = lscn->n_cyl->next;
		cyl = nscn->n_cyl->content;
		lcyl = lscn->n_cyl->content;
		lcyl->h = cyl->h;
		lcyl->d = cyl->d;
		color_copy(&lcyl->trgb, &cyl->trgb);
		mtrx4_x_point(&lcyl->p, &lookat->m, &cyl->p);
		mtrx4_x_vctr(&lcyl->v, &lookat->m, &cyl->v.nxyz);
		v_fill(&lcyl->v);
		if (nscn->n_cyl->next != NULL)
			nscn->n_cyl = nscn->n_cyl->next;
		lscn->n_cntr.cyl++;
	}
}

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

	nscn->n_sqr = nscn->frst_sqr;
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
	cnvrse2local(lscn, nscn);
	print_node(lscn);
	rays_node(lscn, nscn);
}
