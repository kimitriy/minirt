/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lookat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:11:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/15 13:42:52 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	null_lookat(t_look_at *lookat)
{
	if (lookat->tmp != '+')	
		v_null(&lookat->vTMP);
	v_null(&lookat->vF);
	v_null(&lookat->vR);
	v_null(&lookat->vUP);
}

void	v_tmp_make(t_vctr *vf, t_vctr *tmp, t_look_at *lkt)
{
	if (lkt->tmp != '+')
	{
		tmp->xyz.x = 0;
		if (vf->nxyz.y == 1)
		{
			tmp->xyz.y = 0;
			tmp->xyz.z = -1;
		}
		else if (vf->xyz.y == -1)
		{
			tmp->xyz.y = 0;
			tmp->xyz.z = 1;
		}
		else
		{
			tmp->xyz.y = 1;
			tmp->xyz.z = 0;
		}
	}
	v_fill(tmp);
}

void	look_at_mtrx(t_look_at *lookat, t_vctr *vF, t_point *p)
{
	null_lookat(lookat);
	v_n_prdct(&lookat->vF.xyz, &vF->nxyz, -1);
	v_fill(&lookat->vF);
	v_tmp_make(&lookat->vF, &lookat->vTMP, lookat);
	// v_fill(&lookat->vTMP);
	v_crss_prdct(&lookat->vR.xyz, &lookat->vF.nxyz, &lookat->vTMP.nxyz);
	v_fill(&lookat->vR);
	v_crss_prdct(&lookat->vUP.xyz, &lookat->vR.nxyz, &lookat->vF.nxyz);
	v_fill(&lookat->vUP);
	lookat->m.m[0][0] = lookat->vR.nxyz.x;
	lookat->m.m[0][1] = lookat->vR.nxyz.y;
	lookat->m.m[0][2] = lookat->vR.nxyz.z;
	lookat->m.m[0][3] = -v_x_point_prdct(&lookat->vR.nxyz, p);
	lookat->m.m[1][0] = lookat->vUP.nxyz.x;
	lookat->m.m[1][1] = lookat->vUP.nxyz.y;
	lookat->m.m[1][2] = lookat->vUP.nxyz.z;
	lookat->m.m[1][3] = -v_x_point_prdct(&lookat->vUP.nxyz, p);
	lookat->m.m[2][0] = lookat->vF.nxyz.x;
	lookat->m.m[2][1] = lookat->vF.nxyz.y;
	lookat->m.m[2][2] = lookat->vF.nxyz.z;
	lookat->m.m[2][3] = -v_x_point_prdct(&lookat->vF.nxyz, p);
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
		// p_copy(&llght->p, &lght->p);
		// llght->p.x = lght->p.x;
		// llght->p.y = lght->p.y;
		// llght->p.z = lght->p.z;
		color_copy(&llght->trgb, &lght->trgb);
		// llght->trgb.t = lght->trgb.t;
		// llght->trgb.r = lght->trgb.r;
		// llght->trgb.g = lght->trgb.g;
		// llght->trgb.b = lght->trgb.b;
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
		// p_copy(&lpln->p, &pln->p);
		// lpln->p.x = pln->p.x;
		// lpln->p.y = pln->p.y;
		// lpln->p.z = pln->p.z;
		// v_copy(&lpln->v, &pln->v);
		// lpln->v.nxyz.x = pln->v.nxyz.x;
		// lpln->v.nxyz.y = pln->v.nxyz.y;
		// lpln->v.nxyz.z = pln->v.nxyz.z;
		// v_fill(&lpln->v);
		color_copy(&lpln->trgb, &pln->trgb);
		// lpln->trgb.t = pln->trgb.t;
		// lpln->trgb.r = pln->trgb.r;
		// lpln->trgb.g = pln->trgb.g;
		// lpln->trgb.b = pln->trgb.b;
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
		// p_copy(&lsphr->p, &sphr->p);
		// lsphr->p.x = sphr->p.x;
		// lsphr->p.y = sphr->p.y;
		// lsphr->p.z = sphr->p.z;
		lsphr->d = sphr->d;
		color_copy(&lsphr->trgb, &sphr->trgb);
		// lsphr->trgb.t = sphr->trgb.t;
		// lsphr->trgb.r = sphr->trgb.r;
		// lsphr->trgb.g = sphr->trgb.g;
		// lsphr->trgb.b = sphr->trgb.b;
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
		// p_copy(&lcyl->p, &cyl->p);
		// lcyl->p.x = cyl->p.x;
		// lcyl->p.y = cyl->p.y;
		// lcyl->p.z = cyl->p.z;
		// v_copy(&lcyl->v, &cyl->v);
		// lcyl->v.nxyz.x = cyl->v.nxyz.x;
		// lcyl->v.nxyz.y = cyl->v.nxyz.y;
		// lcyl->v.nxyz.z = cyl->v.nxyz.z;
		lcyl->h = cyl->h;
		lcyl->d = cyl->d;
		color_copy(&lcyl->trgb, &cyl->trgb);
		// lcyl->trgb.t = cyl->trgb.t;
		// lcyl->trgb.r = cyl->trgb.r;
		// lcyl->trgb.g = cyl->trgb.g;
		// lcyl->trgb.b = cyl->trgb.b;
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
		// p_copy(&lsqr->p, &sqr->p);
		// v_copy(&lsqr->v, &sqr->v);
		// v_copy(&lsqr->v_tmp, &sqr->v_tmp);
		if (v_are_collinear(&sqr->v, &sqr->v_tmp) == 1)
			v_tmp_make(&sqr->v, &sqr->v_tmp, lookat);
		lsqr->side = sqr->side;
		color_copy(&lsqr->trgb, &sqr->trgb);
		mtrx4_x_point(&lsqr->p, &lookat->m, &sqr->p);
		mtrx4_x_vctr(&lsqr->v, &lookat->m, &sqr->v.nxyz);
		// v_fill(&lsqr->v);
		mtrx4_x_vctr(&lsqr->v_tmp, &lookat->m, &sqr->v_tmp.nxyz);
		// v_fill(&lsqr->v_tmp);
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
		// p_copy(&ltrngl->p1, &trngl->p1);
		// ltrngl->p1.x = trngl->p1.x;
		// ltrngl->p1.y = trngl->p1.y;
		// ltrngl->p1.z = trngl->p1.z;
		// p_copy(&ltrngl->p2, &trngl->p2);
		// ltrngl->p2.x = trngl->p2.x;
		// ltrngl->p2.y = trngl->p2.y;
		// ltrngl->p2.z = trngl->p2.z;
		// p_copy(&ltrngl->p3, &trngl->p3);
		// ltrngl->p3.x = trngl->p3.x;
		// ltrngl->p3.y = trngl->p3.y;
		// ltrngl->p3.z = trngl->p3.z;
		// v_copy(&ltrngl->n, &trngl->n);
		// ltrngl->n.nxyz.x = trngl->n.nxyz.x;
		// ltrngl->n.nxyz.y = trngl->n.nxyz.y;
		// ltrngl->n.nxyz.z = trngl->n.nxyz.z;
		color_copy(&ltrngl->trgb, &trngl->trgb);
		// ltrngl->trgb.t = trngl->trgb.t;
		// ltrngl->trgb.r = trngl->trgb.r;
		// ltrngl->trgb.g = trngl->trgb.g;
		// ltrngl->trgb.b = trngl->trgb.b;
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
	t_look_at 	lookat;

	//nscn->n_cam = nscn->frst_cam;
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
