/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lookat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:11:59 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 02:07:35 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	null_lookat(t_look_at *lookat)
{
	v_null(&lookat->vF);
	v_null(&lookat->vTMP);
	v_null(&lookat->vR);
	v_null(&lookat->vUP);
}

void	look_at_mtrx(t_vctr *vF, t_point *p, t_look_at *lookat)
{
	null_lookat(lookat);
	lookat->vF.nxyz.x = -vF->nxyz.x;
	lookat->vF.nxyz.y = -vF->nxyz.y;
	lookat->vF.nxyz.z = -vF->nxyz.z;
	v_fill(&lookat->vF);
	lookat->vTMP.xyz.x = 0;
	lookat->vTMP.xyz.y = 1;
	lookat->vTMP.xyz.z = 0;
	v_fill(&lookat->vTMP);
	v_crss_prdct(&lookat->vR.xyz, &lookat->vTMP.nxyz, &lookat->vF.nxyz);
	v_fill(&lookat->vR);
	v_crss_prdct(&lookat->vUP.xyz, &lookat->vF.nxyz, &lookat->vR.nxyz);
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
	cam = nscn->n_cam->content;
	lcam = lscn->n_cam->content;
	lcam->fov = cam->fov;
	nscn->n_cam = nscn->n_cam->next;
	lscn->n_cntr.cam++;
}

void	cnvrse_lght(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_lght	*lght;
	t_lght	*llght;

	while (lscn->n_cntr.lght < nscn->n_cntr.lght)
	{
		make_t_lght(lscn);
		lght = nscn->n_lght->content;
		llght = lscn->n_lght->content;
		llght->p.x = lght->p.x;
		llght->p.y = lght->p.y;
		llght->p.z = lght->p.z;
		llght->r = lght->r;
		llght->g = lght->g;
		llght->b = lght->b;
		llght->lvl = lght->lvl;
		mtrx4_x_point(&llght->p, &lookat->m, &lght->p);
		nscn->n_lght = nscn->n_lght->next;
		lscn->n_cntr.lght++;
	}
}

void	cnvrse_pln(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_pln	*pln;
	t_pln	*lpln;

	while (lscn->n_cntr.pln < nscn->n_cntr.pln)
	{
		make_t_pln(lscn);
		pln = nscn->n_pln->content;
		lpln = lscn->n_pln->content;
		lpln->p.x = pln->p.x;
		lpln->p.y = pln->p.y;
		lpln->p.z = pln->p.z;
		lpln->v.nxyz.x = pln->v.nxyz.x;
		lpln->v.nxyz.y = pln->v.nxyz.y;
		lpln->v.nxyz.z = pln->v.nxyz.z;
		lpln->r = pln->r;
		lpln->g = pln->g;
		lpln->b = pln->b;
		mtrx4_x_point(&lpln->p, &lookat->m, &pln->p);
		mtrx4_x_vctr(&lpln->v.nxyz, &lookat->m, &pln->v.nxyz);
		v_fill(&lpln->v);
		nscn->n_pln = nscn->n_pln->next;
		lscn->n_cntr.pln++;
	}
}

void	cnvrse_sphr(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_sphr	*sphr;
	t_sphr	*lsphr;

	while (lscn->n_cntr.sphr < nscn->n_cntr.sphr)
	{
		make_t_sphr(lscn);
		sphr = nscn->n_sphr->content;
		lsphr = lscn->n_sphr->content;
		lsphr->p.x = sphr->p.x;
		lsphr->p.y = sphr->p.y;
		lsphr->p.z = sphr->p.z;
		lsphr->d = sphr->d;
		lsphr->r = sphr->r;
		lsphr->g = sphr->g;
		lsphr->b = sphr->b;
		mtrx4_x_point(&lsphr->p, &lookat->m, &sphr->p);
		nscn->n_sphr = nscn->n_sphr->next;
		lscn->n_cntr.sphr++;
	}
}

void	cnvrse_cyl(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_cyl	*cyl;
	t_cyl	*lcyl;

	while (lscn->n_cntr.cyl < nscn->n_cntr.cyl)
	{
		make_t_cyl(lscn);
		cyl = nscn->n_cyl->content;
		lcyl = lscn->n_cyl->content;
		lcyl->p.x = cyl->p.x;
		lcyl->p.y = cyl->p.y;
		lcyl->p.z = cyl->p.z;
		lcyl->v.nxyz.x = cyl->v.nxyz.x;
		lcyl->v.nxyz.y = cyl->v.nxyz.y;
		lcyl->v.nxyz.z = cyl->v.nxyz.z;
		lcyl->h = cyl->h;
		lcyl->d = cyl->d;
		lcyl->r = cyl->r;
		lcyl->g = cyl->g;
		lcyl->b = cyl->b;
		mtrx4_x_point(&lcyl->p, &lookat->m, &cyl->p);
		mtrx4_x_vctr(&lcyl->v.nxyz, &lookat->m, &cyl->v.nxyz);
		v_fill(&lcyl->v);
		nscn->n_cyl = nscn->n_cyl->next;
		lscn->n_cntr.cyl++;
	}
}

void	cnvrse_sqr(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_sqr	*sqr;
	t_sqr	*lsqr;

	while (lscn->n_cntr.sqr < nscn->n_cntr.sqr)
	{
		make_t_sqr(lscn);
		sqr = nscn->n_sqr->content;
		lsqr = lscn->n_sqr->content;
		lsqr->p.x = sqr->p.x;
		lsqr->p.y = sqr->p.y;
		lsqr->p.z = sqr->p.z;
		lsqr->v.nxyz.x = sqr->v.nxyz.x;
		lsqr->v.nxyz.y = sqr->v.nxyz.y;
		lsqr->v.nxyz.z = sqr->v.nxyz.z;
		lsqr->side = sqr->side;
		lsqr->r = sqr->r;
		lsqr->g = sqr->g;
		lsqr->b = sqr->b;
		mtrx4_x_point(&lsqr->p, &lookat->m, &sqr->p);
		mtrx4_x_vctr(&lsqr->v.nxyz, &lookat->m, &sqr->v.nxyz);
		v_fill(&lsqr->v);
		nscn->n_sqr = nscn->n_sqr->next;
		lscn->n_cntr.sqr++;
	}
}

void	cnvrse_trngl(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_trngl	*trngl;
	t_trngl	*ltrngl;

	while (lscn->n_cntr.trngl < nscn->n_cntr.trngl)
	{
		make_t_trngl(lscn);
		trngl = nscn->n_trngl->content;
		ltrngl = lscn->n_trngl->content;
		ltrngl->p1.x = trngl->p1.x;
		ltrngl->p1.y = trngl->p1.y;
		ltrngl->p1.z = trngl->p1.z;
		ltrngl->p2.x = trngl->p2.x;
		ltrngl->p2.y = trngl->p2.y;
		ltrngl->p2.z = trngl->p2.z;
		ltrngl->p3.x = trngl->p3.x;
		ltrngl->p3.y = trngl->p3.y;
		ltrngl->p3.z = trngl->p3.z;
		ltrngl->n.nxyz.x = trngl->n.nxyz.x;
		ltrngl->n.nxyz.y = trngl->n.nxyz.y;
		ltrngl->n.nxyz.z = trngl->n.nxyz.z;
		mtrx4_x_point(&ltrngl->p1, &lookat->m, &trngl->p1);
		mtrx4_x_point(&ltrngl->p2, &lookat->m, &trngl->p2);
		mtrx4_x_point(&ltrngl->p3, &lookat->m, &trngl->p3);
		mtrx4_x_vctr(&ltrngl->n.nxyz, &lookat->m, &trngl->n.nxyz);
		v_fill(&ltrngl->n);
		nscn->n_trngl = nscn->n_trngl->next;
		lscn->n_cntr.trngl++;
	}
}

t_scn	*cnvrse2local(t_scn *nscn)
{
	t_scn		*lscn;
	t_cam		*cam;
	t_look_at 	lookat;

	cam = nscn->n_cam->content;
	lscn = make_t_scn();
	look_at_mtrx(&cam->v, &cam->p, &lookat);
	lscn->n_rsltn = nscn->n_rsltn;
	lscn->n_ambnt = nscn->n_ambnt;
	get_cam_fov(nscn, lscn);
	cnvrse_lght(nscn, lscn, &lookat);
	cnvrse_pln(nscn, lscn, &lookat);
	cnvrse_sphr(nscn, lscn, &lookat);
	cnvrse_cyl(nscn, lscn, &lookat);
	cnvrse_sqr(nscn, lscn, &lookat);
	cnvrse_trngl(nscn, lscn, &lookat);

	return (lscn);
}

void	lookat_node(t_scn *nscn)
{
	t_scn	*cam1scn;

	//cam1scn = NULL;

	cam1scn = cnvrse2local(nscn);
	//print_node(cam1scn);
	rays_node(cam1scn);
}
