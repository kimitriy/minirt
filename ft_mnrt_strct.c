/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:51:13 by rburton           #+#    #+#             */
/*   Updated: 2021/01/27 18:43:21 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	make_t_rsltn(t_scn *scn)
{
	scn->n_rsltn.x = 0;
	scn->n_rsltn.y = 0;
}

void	make_t_ambnt(t_scn *scn)
{
	scn->n_ambnt.lvl = 0;
	scn->n_ambnt.trgb.t = 0;
	scn->n_ambnt.trgb.r = 0;
	scn->n_ambnt.trgb.g = 0;
	scn->n_ambnt.trgb.b = 0;
}

void	make_t_cam(t_scn *scn)
{
	t_cam	*new_cam; //малочить сука!!!
	
	if (!(new_cam = (t_cam*)malloc(1 * sizeof(t_cam))))
		new_cam = NULL;
	new_cam->p.x = 0;
	new_cam->p.y = 0;
	new_cam->p.z = 0;
	new_cam->v.xyz.x = 0;
	new_cam->v.xyz.y = 0;
	new_cam->v.xyz.z = 0;
	v_null(&new_cam->v);
	new_cam->fov = 0;
	new_cam->nxt = NULL;
	ft_lstadd_front(&scn->n_cam, ft_lstnew(new_cam));
}

void	make_t_lght(t_scn *scn)
{
	t_lght	*new_lght;

	if (!(new_lght = (t_lght*)malloc(1 * sizeof(t_lght))))
		new_lght = NULL;
	new_lght->p.x = 0;
	new_lght->p.y = 0;
	new_lght->p.z = 0;
	new_lght->lvl = 0;
	new_lght->trgb.t = 0;
	new_lght->trgb.r = 0;
	new_lght->trgb.g = 0;
	new_lght->trgb.b = 0;
	new_lght->nxt = NULL;
	ft_lstadd_front(&scn->n_lght, ft_lstnew(new_lght));
}

void	make_t_pln(t_scn *scn)
{
	t_pln	*new_pln;

	if (!(new_pln = (t_pln*)malloc(1 * sizeof(t_pln))))
		new_pln = NULL;
	new_pln->p.x = 0;
	new_pln->p.y = 0;
	new_pln->p.z = 0;
	new_pln->v.xyz.x = 0;
	new_pln->v.xyz.y = 0;
	new_pln->v.xyz.z = 0;
	v_null(&new_pln->v);
	new_pln->trgb.t = 0;
	new_pln->trgb.r = 0;
	new_pln->trgb.g = 0;
	new_pln->trgb.b = 0;
	new_pln->nxt = NULL;
	ft_lstadd_front(&scn->n_pln, ft_lstnew(new_pln));
}

void	make_t_sphr(t_scn *scn)
{
	t_sphr	*new_sphr;
	
	if (!(new_sphr = (t_sphr*)malloc(1 * sizeof(t_sphr))))
		new_sphr = NULL;
	new_sphr->p.x = 0;
	new_sphr->p.y = 0;
	new_sphr->p.z = 0;
	new_sphr->d = 0;
	new_sphr->trgb.t = 0;
	new_sphr->trgb.r = 0;
	new_sphr->trgb.g = 0;
	new_sphr->trgb.b = 0;
	new_sphr->nxt = NULL;
	ft_lstadd_front(&scn->n_sphr, ft_lstnew(new_sphr));
}

void	make_t_cyl(t_scn *scn)
{
	t_cyl	*new_cyl;

	if (!(new_cyl = (t_cyl*)malloc(1 * sizeof(t_cyl))))
		new_cyl = NULL;
	new_cyl->p.x = 0;
	new_cyl->p.y = 0;
	new_cyl->p.z = 0;
	new_cyl->v.xyz.x = 0;
	new_cyl->v.xyz.y = 0;
	new_cyl->v.xyz.z = 0;
	v_null(&new_cyl->v);
	new_cyl->d = 0;
	new_cyl->h = 0;
	new_cyl->trgb.t = 0;
	new_cyl->trgb.r = 0;
	new_cyl->trgb.g = 0;
	new_cyl->trgb.b = 0;
	new_cyl->nxt = NULL;
	ft_lstadd_front(&scn->n_cyl, ft_lstnew(new_cyl));
}

void	make_t_sqr(t_scn *scn)
{
	t_sqr	*new_sqr;

	if (!(new_sqr = (t_sqr*)malloc(1 * sizeof(t_sqr))))
		new_sqr = NULL;
	new_sqr->p.x = 0;
	new_sqr->p.y = 0;
	new_sqr->p.z = 0;
	new_sqr->v.xyz.x = 0;
	new_sqr->v.xyz.y = 0;
	new_sqr->v.xyz.z = 0;
	v_null(&new_sqr->v);
	new_sqr->side = 0;
	new_sqr->trgb.t = 0;
	new_sqr->trgb.r = 0;
	new_sqr->trgb.g = 0;
	new_sqr->trgb.b = 0;
	new_sqr->nxt = NULL;
	ft_lstadd_front(&scn->n_sqr, ft_lstnew(new_sqr));
}

void	make_t_trngl(t_scn *scn)
{
	t_trngl	*new_trngl;

	if (!(new_trngl = (t_trngl*)malloc(1 * sizeof(t_trngl))))
		new_trngl = NULL;
	new_trngl->p1.x = 0;
	new_trngl->p1.y = 0;
	new_trngl->p1.z = 0;
	new_trngl->p2.x = 0;
	new_trngl->p2.y = 0;
	new_trngl->p2.z = 0;
	new_trngl->p3.x = 0;
	new_trngl->p3.y = 0;
	new_trngl->p3.z = 0;
	new_trngl->n.xyz.x = 0;
	new_trngl->n.xyz.y = 0;
	new_trngl->n.xyz.z = 0;
	v_null(&new_trngl->n);
	new_trngl->trgb.t = 0;
	new_trngl->trgb.r = 0;
	new_trngl->trgb.g = 0;
	new_trngl->trgb.b = 0;
	new_trngl->nxt = NULL;
	ft_lstadd_front(&scn->n_trngl, ft_lstnew(new_trngl));
}

void	make_t_cntr(t_scn *scn)
{
	scn->n_cntr.cam = 0;
	scn->n_cntr.lght = 0;
	scn->n_cntr.pln = 0;
	scn->n_cntr.sphr = 0;
	scn->n_cntr.cyl = 0;
	scn->n_cntr.sqr = 0;
	scn->n_cntr.trngl = 0;
}

t_scn	*make_t_scn(void)
{
    t_scn   *scn;

	if (!(scn = (t_scn*)malloc(1 * sizeof(t_scn))))
		return (NULL);
	make_t_cntr(scn);
	make_t_rsltn(scn);
	make_t_ambnt(scn);
	return (scn);
}

//-3.40282300000000000000000000000000000000

void	nprsr_reset_counters(t_prsr *nprsr)
{
	nprsr->i = 0;
    nprsr->j = 0;
    nprsr->n = 0;
}

void	nprsr_nullt_fields(t_prsr *nprsr)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		nprsr->r[i] = '\0';
		nprsr->g[i] = '\0';
		nprsr->b[i] = '\0';
		nprsr->fov[i] = '\0';
		nprsr->rx[i] = '\0';
		nprsr->ry[i] = '\0';
	}
	i = -1;
	while (++i < 42)
	{
		nprsr->x[i] = '\0';
		nprsr->y[i] = '\0';
		nprsr->z[i] = '\0';
		nprsr->x2[i] = '\0';
		nprsr->y2[i] = '\0';
		nprsr->z2[i] = '\0';
		nprsr->x3[i] = '\0';
		nprsr->y3[i] = '\0';
		nprsr->z3[i] = '\0';
		nprsr->nx[i] = '\0';
		nprsr->ny[i] = '\0';
		nprsr->nz[i] = '\0';
		nprsr->lvl[i] = '\0';
		nprsr->side[i] = '\0';
		nprsr->d[i] = '\0';
		nprsr->h[i] = '\0';
	}
}

t_prsr	make_t_prsr(void)
{
	t_prsr  nprsr;

	nprsr_reset_counters(&nprsr);
	nprsr_nullt_fields(&nprsr);
	return (nprsr);
}

void	strct_node(char **scn_arr, int size)
{
	t_scn   *scn;
	t_prsr  np;

	scn = make_t_scn();
	np = make_t_prsr();

	prsr(scn_arr, size, scn, &np);
	//rays_node(&scn);
	//v_node();
	//print_node(scn);
	lookat_node(scn);
	
}

	//v_node();
	//cnvs_node(&scn);
	//print_node(&scn);
	//mlx_node();