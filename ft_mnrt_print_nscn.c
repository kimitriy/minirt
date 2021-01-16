/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_print_nscn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:46:13 by rburton           #+#    #+#             */
/*   Updated: 2021/01/16 15:06:24 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    print_cam(t_scn *nscn)
{
    int     i;
    t_cam   *cam;

    cam = NULL;
	
    i = 0;
    while (i < nscn->n_cntr.cam)
    {
    	cam = nscn->n_cam->content;
        printf("nscn->n_cam->x:%f\n", cam->x);
        printf("nscn->n_cam->y:%f\n", cam->y);
        printf("nscn->n_cam->z:%f\n", cam->z);
        printf("nscn->n_cam->nx:%f\n", cam->nx);
        printf("nscn->n_cam->ny:%f\n", cam->ny);
        printf("nscn->n_cam->nz:%f\n", cam->nz);
        printf("nscn->n_cam->fov:%d\n", cam->fov);
        nscn->n_cam = nscn->n_cam->next;
        i++;
    }
}

void    print_light(t_scn *nscn)
{
    int		i;
    t_lght	*lght;

    lght = NULL;
    
    i = 0;
    while (i < nscn->n_cntr.lght)
    {
        lght = nscn->n_lght->content;
		printf("nscn->n_lght->x:%f\n", lght->x);
        printf("nscn->n_lght->y:%f\n", lght->y);
        printf("nscn->n_lght->z:%f\n", lght->z);
        printf("nscn->n_lght->lvl:%f\n", lght->lvl);
        printf("nscn->n_lght->r:%d\n", lght->r);
        printf("nscn->n_lght->g:%d\n", lght->g);
        printf("nscn->n_lght->b:%d\n", lght->b);
        nscn->n_lght = nscn->n_lght->next;
        i++;
    }
}

void    print_pln(t_scn *nscn)
{
    int		i;
    t_pln	*pln;

    pln = NULL;
    
    i = 0;
    while (i < nscn->n_cntr.pln)
    {
        pln = nscn->n_pln->content;
		printf("nscn->n_pln->x:%f\n", pln->x);
        printf("nscn->n_pln->y:%f\n", pln->y);
        printf("nscn->n_pln->z:%f\n", pln->z);
        printf("nscn->n_pln->nx:%f\n", pln->nx);
        printf("nscn->n_pln->ny:%f\n", pln->ny);
        printf("nscn->n_pln->nz:%f\n", pln->nz);
        printf("nscn->n_pln->r:%d\n", pln->r);
        printf("nscn->n_pln->g:%d\n", pln->g);
        printf("nscn->n_pln->b:%d\n", pln->b);
        nscn->n_pln = nscn->n_pln->next;
        i++;
    }
}

void    print_sphr(t_scn *nscn)
{
    int		i;
    t_sphr	*sphr;

    sphr = NULL;
    
    i = 0;
    while (i < nscn->n_cntr.sphr)
    {
        sphr = nscn->n_sphr->content;
		printf("nscn->n_sphr->x:%f\n", sphr->x);
        printf("nscn->n_sphr->y:%f\n", sphr->y);
        printf("nscn->n_sphr->z:%f\n", sphr->z);
        printf("nscn->n_sphr->d:%f\n", sphr->d);
        printf("nscn->n_sphr->r:%d\n", sphr->r);
        printf("nscn->n_sphr->g:%d\n", sphr->g);
        printf("nscn->n_sphr->b:%d\n", sphr->b);
        nscn->n_sphr = nscn->n_sphr->next;
        i++;
    }
}

void    print_cyl(t_scn *nscn)
{
    int		i;
    t_cyl	*cyl;

    cyl = NULL;
    
    i = 0;
    while (i < nscn->n_cntr.cyl)
    {
        cyl = nscn->n_cyl->content;
		printf("nscn->n_cyl->x:%f\n", cyl->x);
        printf("nscn->n_cyl->y:%f\n", cyl->y);
        printf("nscn->n_cyl->z:%f\n", cyl->z);
        printf("nscn->n_cyl->nx:%f\n", cyl->nx);
        printf("nscn->n_cyl->ny:%f\n", cyl->ny);
        printf("nscn->n_cyl->nz:%f\n", cyl->nz);
        printf("nscn->n_cyl->d:%f\n", cyl->d);
        printf("nscn->n_cyl->h:%f\n", cyl->h);
        printf("nscn->n_cyl->r:%d\n", cyl->r);
        printf("nscn->n_cyl->g:%d\n", cyl->g);
        printf("nscn->n_cyl->b:%d\n", cyl->b);
        nscn->n_cyl = nscn->n_cyl->next;
        i++;
    }
}

void    print_sqr(t_scn *nscn)
{
    int		i;
    t_sqr	*sqr;

    sqr = NULL;
    
    i = 0;
    while (i < nscn->n_cntr.sqr)
    {
        sqr = nscn->n_sqr->content;
		printf("nscn->n_sqr->x:%f\n", sqr->x);
        printf("nscn->n_sqr->y:%f\n", sqr->y);
        printf("nscn->n_sqr->z:%f\n", sqr->z);
        printf("nscn->n_sqr->nx:%f\n", sqr->nx);
        printf("nscn->n_sqr->ny:%f\n", sqr->ny);
        printf("nscn->n_sqr->nz:%f\n", sqr->nz);
        printf("nscn->n_sqr->side:%f\n", sqr->side);
        printf("nscn->n_sqr->r:%d\n", sqr->r);
        printf("nscn->n_sqr->g:%d\n", sqr->g);
        printf("nscn->n_sqr->b:%d\n", sqr->b);
        nscn->n_sqr = nscn->n_sqr->next;
        i++;
    }
}

void    print_trngl(t_scn *nscn)
{
    int		i;
    t_trngl	*trngl;

    trngl = NULL;
    
    i = 0;
    while (i < nscn->n_cntr.trngl)
    {
        trngl = nscn->n_trngl->content;
		printf("nscn->n_trngl->x1:%f\n", trngl->x1);
        printf("nscn->n_trngl->y2:%f\n", trngl->y1);
        printf("nscn->n_trngl->z3:%f\n", trngl->z1);
        printf("nscn->n_trngl->x2:%f\n", trngl->x2);
        printf("nscn->n_trngl->y2:%f\n", trngl->y2);
        printf("nscn->n_trngl->z2:%f\n", trngl->z2);
        printf("nscn->n_trngl->x3:%f\n", trngl->x3);
        printf("nscn->n_trngl->y3:%f\n", trngl->y3);
        printf("nscn->n_trngl->z3:%f\n", trngl->z3);
        printf("nscn->n_trngl->r:%d\n", trngl->r);
        printf("nscn->n_trngl->g:%d\n", trngl->g);
        printf("nscn->n_trngl->b:%d\n", trngl->b);
        nscn->n_trngl = nscn->n_trngl->next;
        i++;
    }
}

void	print_node(t_scn *nscn)
{
	print_cam(nscn);
	print_light(nscn);
    print_pln(nscn);
    print_sphr(nscn);
    print_cyl(nscn);
    print_sqr(nscn);
    print_trngl(nscn);
}