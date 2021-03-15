/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_print_nscn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:46:13 by rburton           #+#    #+#             */
/*   Updated: 2021/03/15 13:47:31 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    print_save(t_scn *scn)
{
    printf("--save: (%c)\n", scn->save);
}

void    print_res(t_scn *scn)
{
    printf("resolution: (%d, %d)\n", scn->n_rsltn.x, scn->n_rsltn.y);
}

void    print_ambnt(t_scn *scn)
{
    printf("ambient: lvl:%f, trgb(%d, %d, %d)\n", scn->n_ambnt.lvl, scn->n_ambnt.trgb.r, scn->n_ambnt.trgb.g, scn->n_ambnt.trgb.b);
}

void    print_cam(t_scn *scn)
{
    int     i;
    t_cam   *cam;

    i = 0;
    scn->n_cam = scn->frst_cam;
    while (i < scn->n_cntr.cam)
    {
    	cam = scn->n_cam->content;
        printf("cam: xyz(%f, %f, %f), nxyz(%f, %f, %f), fov:%d\n", cam->p.x, cam->p.y, cam->p.z, cam->v.nxyz.x, cam->v.nxyz.y, cam->v.nxyz.z, cam->fov);
        scn->n_cam = scn->n_cam->next;
        i++;
    }
    scn->n_cam = scn->frst_cam;
}

void    print_light(t_scn *scn)
{
    int		i;
    t_lght	*lght;

    i = 0;
    scn->n_lght = scn->frst_lght;
    while (i < scn->n_cntr.lght)
    {
        lght = scn->n_lght->content;
		printf("lght: xyz(%f, %f, %f), lvl:%f, trgb(%d, %d, %d, %d)\n", lght->p.x, lght->p.y, lght->p.z, lght->lvl, lght->trgb.t, lght->trgb.r, lght->trgb.g, lght->trgb.b);
        scn->n_lght = scn->n_lght->next;
        i++;
    }
    scn->n_lght = scn->frst_lght;
}

void    print_pln(t_scn *scn)
{
    int		i;
    t_pln	*pln;
    
    i = 0;
    scn->n_pln = scn->frst_pln;
    while (i < scn->n_cntr.pln)
    {
        pln = scn->n_pln->content;
		printf("pln: xyz(%f, %f, %f), nxyz(%f, %f, %f), trgb(%d, %d, %d, %d)\n", pln->p.x, pln->p.y, pln->p.z, pln->v.nxyz.x, pln->v.nxyz.y, pln->v.nxyz.z, pln->trgb.t, pln->trgb.r, pln->trgb.g, pln->trgb.b);
        scn->n_pln = scn->n_pln->next;
        i++;
    }
    scn->n_pln = scn->frst_pln;
}

void    print_sphr(t_scn *scn)
{
    int		i;
    t_sphr	*sphr;

    i = 0;
    scn->n_sphr = scn->frst_sphr;
    while (i < scn->n_cntr.sphr)
    {
        sphr = scn->n_sphr->content;
        printf("sph: xyz(%f, %f, %f), d:%f, trgb(%d, %d, %d, %d)\n", sphr->p.x, sphr->p.y, sphr->p.z, sphr->d, sphr->trgb.t, sphr->trgb.r, sphr->trgb.g, sphr->trgb.b);
        scn->n_sphr = scn->n_sphr->next;
        i++;
    }
    scn->n_sphr = scn->frst_sphr;
}

void    print_cyl(t_scn *scn)
{
    int		i;
    t_cyl	*cyl;

    i = 0;
    scn->n_cyl = scn->frst_cyl;
    while (i < scn->n_cntr.cyl)
    {
        cyl = scn->n_cyl->content;
		printf("cyl: xyz(%f, %f, %f), nxyz(%f, %f, %f), d:%f, h:%f, trgb(%d, %d, %d, %d)\n", cyl->p.x, cyl->p.y, cyl->p.z, cyl->v.nxyz.x, cyl->v.nxyz.y, cyl->v.nxyz.z, cyl->d, cyl->h, cyl->trgb.t, cyl->trgb.r, cyl->trgb.g, cyl->trgb.b);
        scn->n_cyl = scn->n_cyl->next;
        i++;
    }
    scn->n_cyl = scn->frst_cyl;
}

void    print_sqr(t_scn *scn)
{
    int		i;
    t_sqr	*sqr;

    i = 0;
    scn->n_sqr = scn->frst_sqr;
    while (i < scn->n_cntr.sqr)
    {
        sqr = scn->n_sqr->content;
		printf("sqr: xyz(%f, %f, %f), nxyz(%f, %f, %f), side:%f, trgb(%d, %d, %d, %d)\n", sqr->p.x, sqr->p.y, sqr->p.z, sqr->v.nxyz.x, sqr->v.nxyz.y, sqr->v.nxyz.z, sqr->side, sqr->trgb.t, sqr->trgb.r, sqr->trgb.g, sqr->trgb.b);
        scn->n_sqr = scn->n_sqr->next;
        i++;
    }
    scn->n_sqr = scn->frst_sqr;
}

void    print_trngl(t_scn *scn)
{
    int		i;
    t_trngl	*trngl;

    i = 0;
    scn->n_trngl = scn->frst_trngl;
    while (i < scn->n_cntr.trngl)
    {
        trngl = scn->n_trngl->content;
		printf("trngl: xyz1(%f, %f, %f), xyz2(%f, %f, %f), xyz3(%f, %f, %f), trgb(%d, %d, %d, %d)\n", trngl->p1.x, trngl->p1.y, trngl->p1.z, trngl->p2.x, trngl->p2.y, trngl->p2.z, trngl->p3.x, trngl->p3.y, trngl->p3.z, trngl->trgb.t, trngl->trgb.r, trngl->trgb.g, trngl->trgb.b);
        scn->n_trngl = scn->n_trngl->next;
        i++;
    }
    scn->n_trngl = scn->frst_trngl;
}

void	print_node(t_scn *scn)
{
	print_save(scn);
    print_res(scn);
    print_ambnt(scn);
    print_cam(scn);
	print_light(scn);
    print_pln(scn);
    print_sphr(scn);
    print_cyl(scn);
    print_sqr(scn);
    print_trngl(scn);
    write(1, "\n", 1);
}