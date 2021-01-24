/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_print_nscn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:46:13 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 19:44:32 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    print_cam(t_scn *scn)
{
    int     i;
    t_cam   *cam;

    i = 0;
    while (i < scn->n_cntr.cam)
    {
    	cam = scn->n_cam->content;
        printf("scn->n_cam->x:%f\n", cam->p.x);
        printf("scn->n_cam->y:%f\n", cam->p.y);
        printf("scn->n_cam->z:%f\n", cam->p.z);
        printf("scn->n_cam->nx:%f\n", cam->v.nxyz.x);
        printf("scn->n_cam->ny:%f\n", cam->v.nxyz.y);
        printf("scn->n_cam->nz:%f\n", cam->v.nxyz.z);
        printf("scn->n_cam->fov:%d\n", cam->fov);
        scn->n_cam = scn->n_cam->next;
        i++;
    }
    cam = NULL;
}

void    print_light(t_scn *scn)
{
    int		i;
    t_lght	*lght;

    i = 0;
    while (i < scn->n_cntr.lght)
    {
        lght = scn->n_lght->content;
		printf("scn->n_lght->x:%f\n", lght->p.x);
        printf("scn->n_lght->y:%f\n", lght->p.y);
        printf("scn->n_lght->z:%f\n", lght->p.z);
        printf("scn->n_lght->lvl:%f\n", lght->lvl);
        printf("scn->n_lght->r:%d\n", lght->r);
        printf("scn->n_lght->g:%d\n", lght->g);
        printf("scn->n_lght->b:%d\n", lght->b);
        scn->n_lght = scn->n_lght->next;
        i++;
    }
}

void    print_pln(t_scn *scn)
{
    int		i;
    t_pln	*pln;

    // pln = NULL;
    
    i = 0;
    while (i < scn->n_cntr.pln)
    {
        pln = scn->n_pln->content;
		printf("scn->n_pln->x:%f\n", pln->p.x);
        printf("scn->n_pln->y:%f\n", pln->p.y);
        printf("scn->n_pln->z:%f\n", pln->p.z);
        printf("scn->n_pln->nx:%f\n", pln->v.nxyz.x);
        printf("scn->n_pln->ny:%f\n", pln->v.nxyz.y);
        printf("scn->n_pln->nz:%f\n", pln->v.nxyz.z);
        printf("scn->n_pln->r:%d\n", pln->r);
        printf("scn->n_pln->g:%d\n", pln->g);
        printf("scn->n_pln->b:%d\n", pln->b);
        scn->n_pln = scn->n_pln->next;
        i++;
    }
}

void    print_sphr(t_scn *scn)
{
    int		i;
    t_sphr	*sphr;

    // sphr = NULL;
    
    i = 0;
    while (i < scn->n_cntr.sphr)
    {
        sphr = scn->n_sphr->content;
		printf("scn->n_sphr->x:%f\n", sphr->p.x);
        printf("scn->n_sphr->y:%f\n", sphr->p.y);
        printf("scn->n_sphr->z:%f\n", sphr->p.z);
        printf("scn->n_sphr->d:%f\n", sphr->d);
        printf("scn->n_sphr->r:%d\n", sphr->r);
        printf("scn->n_sphr->g:%d\n", sphr->g);
        printf("scn->n_sphr->b:%d\n", sphr->b);
        scn->n_sphr = scn->n_sphr->next;
        i++;
    }
}

void    print_cyl(t_scn *scn)
{
    int		i;
    t_cyl	*cyl;

    // cyl = NULL;
    
    i = 0;
    while (i < scn->n_cntr.cyl)
    {
        cyl = scn->n_cyl->content;
		printf("scn->n_cyl->x:%f\n", cyl->p.x);
        printf("scn->n_cyl->y:%f\n", cyl->p.y);
        printf("scn->n_cyl->z:%f\n", cyl->p.z);
        printf("scn->n_cyl->nx:%f\n", cyl->v.nxyz.x);
        printf("scn->n_cyl->ny:%f\n", cyl->v.nxyz.y);
        printf("scn->n_cyl->nz:%f\n", cyl->v.nxyz.z);
        printf("scn->n_cyl->d:%f\n", cyl->d);
        printf("scn->n_cyl->h:%f\n", cyl->h);
        printf("scn->n_cyl->r:%d\n", cyl->r);
        printf("scn->n_cyl->g:%d\n", cyl->g);
        printf("scn->n_cyl->b:%d\n", cyl->b);
        scn->n_cyl = scn->n_cyl->next;
        i++;
    }
}

void    print_sqr(t_scn *scn)
{
    int		i;
    t_sqr	*sqr;

    // sqr = NULL;
    
    i = 0;
    while (i < scn->n_cntr.sqr)
    {
        sqr = scn->n_sqr->content;
		printf("scn->n_sqr->x:%f\n", sqr->p.x);
        printf("scn->n_sqr->y:%f\n", sqr->p.y);
        printf("scn->n_sqr->z:%f\n", sqr->p.z);
        printf("scn->n_sqr->nx:%f\n", sqr->v.nxyz.x);
        printf("scn->n_sqr->ny:%f\n", sqr->v.nxyz.y);
        printf("scn->n_sqr->nz:%f\n", sqr->v.nxyz.z);
        printf("scn->n_sqr->side:%f\n", sqr->side);
        printf("scn->n_sqr->r:%d\n", sqr->r);
        printf("scn->n_sqr->g:%d\n", sqr->g);
        printf("scn->n_sqr->b:%d\n", sqr->b);
        scn->n_sqr = scn->n_sqr->next;
        i++;
    }
}

void    print_trngl(t_scn *scn)
{
    int		i;
    t_trngl	*trngl;

    // trngl = NULL;
    
    i = 0;
    while (i < scn->n_cntr.trngl)
    {
        trngl = scn->n_trngl->content;
		printf("scn->n_trngl->x1:%f\n", trngl->p1.x);
        printf("scn->n_trngl->y2:%f\n", trngl->p1.y);
        printf("scn->n_trngl->z3:%f\n", trngl->p1.z);
        printf("scn->n_trngl->x2:%f\n", trngl->p2.x);
        printf("scn->n_trngl->y2:%f\n", trngl->p2.y);
        printf("scn->n_trngl->z2:%f\n", trngl->p2.z);
        printf("scn->n_trngl->x3:%f\n", trngl->p3.x);
        printf("scn->n_trngl->y3:%f\n", trngl->p3.y);
        printf("scn->n_trngl->z3:%f\n", trngl->p3.z);
        printf("scn->n_trngl->r:%d\n", trngl->r);
        printf("scn->n_trngl->g:%d\n", trngl->g);
        printf("scn->n_trngl->b:%d\n", trngl->b);
        scn->n_trngl = scn->n_trngl->next;
        i++;
    }
}

void	print_node(t_scn *scn)
{
	print_cam(scn);
	print_light(scn);
    print_pln(scn);
    print_sphr(scn);
    print_cyl(scn);
    print_sqr(scn);
    print_trngl(scn);
}