/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:51:13 by rburton           #+#    #+#             */
/*   Updated: 2021/02/28 05:28:32 by rburton          ###   ########.fr       */
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
	color_make(&scn->n_ambnt.trgb, 0, 0, 0);
}

void	make_t_cam(t_scn *scn)
{
	t_cam	*new_cam; //малочить сука!!!
	
	if (!(new_cam = (t_cam*)malloc(1 * sizeof(t_cam))))
		new_cam = NULL;
	p_make(&new_cam->p, 0, 0, 0);
	v_null(&new_cam->v);
	new_cam->fov = 0;
	new_cam->nxt = NULL;
	ft_lstadd_back(&scn->n_cam, ft_lstnew(new_cam));
}

void	t_lght_null(t_lght *lght)
{
	p_make(&lght->p, 0, 0, 0);
	lght->lvl = 0;
	color_make(&lght->trgb, 0, 0, 0);
	lght->nxt = NULL;
}

void	make_t_lght(t_scn *scn)
{
	t_lght	*new_lght;

	if (!(new_lght = (t_lght*)malloc(1 * sizeof(t_lght))))
		new_lght = NULL;
	t_lght_null(new_lght);
	ft_lstadd_back(&scn->n_lght, ft_lstnew(new_lght));
}

void	make_t_pln(t_scn *scn)
{
	t_pln	*new_pln;

	if (!(new_pln = (t_pln*)malloc(1 * sizeof(t_pln))))
		new_pln = NULL;
	p_make(&new_pln->p, 0, 0, 0);
	v_null(&new_pln->v);
	color_make(&new_pln->trgb, 0, 0, 0);
	new_pln->nxt = NULL;
	ft_lstadd_back(&scn->n_pln, ft_lstnew(new_pln));
}

void	make_t_sphr(t_scn *scn)
{
	t_sphr	*new_sphr;
	
	if (!(new_sphr = (t_sphr*)malloc(1 * sizeof(t_sphr))))
		new_sphr = NULL;
	p_make(&new_sphr->p, 0, 0, 0);
	new_sphr->d = 0;
	color_make(&new_sphr->trgb, 0, 0, 0);
	new_sphr->nxt = NULL;
	ft_lstadd_back(&scn->n_sphr, ft_lstnew(new_sphr));
}

void	make_t_cyl(t_scn *scn)
{
	t_cyl	*new_cyl;

	if (!(new_cyl = (t_cyl*)malloc(1 * sizeof(t_cyl))))
		new_cyl = NULL;
	p_make(&new_cyl->p, 0, 0, 0);
	p_make(&new_cyl->p2, 0, 0, 0);
	v_null(&new_cyl->v);
	v_null(&new_cyl->v2);
	v_null(&new_cyl->n1);
	v_null(&new_cyl->n2);
	new_cyl->d = 0;
	new_cyl->h = 0;
	color_make(&new_cyl->trgb, 0, 0, 0);
	new_cyl->nxt = NULL;
	ft_lstadd_back(&scn->n_cyl, ft_lstnew(new_cyl));
}

void	make_t_sqr(t_scn *scn)
{
	t_sqr	*new_sqr;

	if (!(new_sqr = (t_sqr*)malloc(1 * sizeof(t_sqr))))
		new_sqr = NULL;
	p_make(&new_sqr->p, 0, 0, 0);
	v_null(&new_sqr->v);
	new_sqr->side = 0;
	color_make(&new_sqr->trgb, 0, 0, 0);
	new_sqr->nxt = NULL;
	ft_lstadd_back(&scn->n_sqr, ft_lstnew(new_sqr));
}

void	make_t_trngl(t_scn *scn)
{
	t_trngl	*new_trngl;

	if (!(new_trngl = (t_trngl*)malloc(1 * sizeof(t_trngl))))
		new_trngl = NULL;
	p_make(&new_trngl->p1, 0, 0, 0);
	p_make(&new_trngl->p2, 0, 0, 0);
	p_make(&new_trngl->p3, 0, 0, 0);
	v_null(&new_trngl->n);
	color_make(&new_trngl->trgb, 0, 0, 0);
	new_trngl->nxt = NULL;
	ft_lstadd_back(&scn->n_trngl, ft_lstnew(new_trngl));
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

void	null_frst(t_scn *scn)
{
	scn->frst_cam = NULL;
	scn->frst_cyl = NULL;
	scn->frst_lght = NULL;
	scn->frst_pln = NULL;
	scn->frst_sphr = NULL;
	scn->frst_sqr = NULL;
	scn->frst_trngl = NULL;
}

t_scn	*make_t_scn(void)
{
    t_scn   *scn;

	if (!(scn = (t_scn*)malloc(1 * sizeof(t_scn))))
		return (NULL);
	make_t_cntr(scn);
	make_t_rsltn(scn);
	make_t_ambnt(scn);
	null_frst(scn);
	scn->n_cam = NULL;
	scn->n_lght = NULL;
	scn->n_pln = NULL;
	scn->n_sphr = NULL;
	scn->n_sqr = NULL;
	scn->n_trngl = NULL;
	scn->n_cyl = NULL;
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
	print_node(scn);
	lookat_node(scn);
	
}

	//v_node();
	//cnvs_node(&scn);
	//print_node(&scn);
	//mlx_node();