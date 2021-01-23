/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:51:13 by rburton           #+#    #+#             */
/*   Updated: 2021/01/23 16:47:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	make_t_rsltn(t_scn *nscn)
{
	nscn->n_rsltn.x = 0;
	nscn->n_rsltn.y = 0;
}

void	make_t_ambnt(t_scn *nscn)
{
	nscn->n_ambnt.lvl = 0;
	nscn->n_ambnt.r = 0;
	nscn->n_ambnt.g = 0;
	nscn->n_ambnt.b = 0;
}

void	make_t_cam(t_scn *nscn)
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
	if (nscn->n_cntr.cam == 0)
		nscn->n_cam = ft_lstnew(new_cam);
	else
		ft_lstadd_front(&nscn->n_cam, ft_lstnew(new_cam));
}

void	make_t_lght(t_scn *nscn)
{
	t_lght	*new_lght;

	if (!(new_lght = (t_lght*)malloc(1 * sizeof(t_lght))))
		new_lght = NULL;
	new_lght->p.x = 0;
	new_lght->p.y = 0;
	new_lght->p.z = 0;
	new_lght->lvl = 0;
	new_lght->r = 0;
	new_lght->g = 0;
	new_lght->b = 0;
	new_lght->nxt = NULL;
	if (nscn->n_cntr.lght == 0)
		nscn->n_lght = ft_lstnew(new_lght);
	else
		ft_lstadd_front(&nscn->n_lght, ft_lstnew(new_lght));
}

void	make_t_pln(t_scn *nscn)
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
	new_pln->r = 0;
	new_pln->g = 0;
	new_pln->b = 0;
	new_pln->nxt = NULL;
	if (nscn->n_cntr.pln == 0)
		nscn->n_pln = ft_lstnew(new_pln);
	else
		ft_lstadd_front(&nscn->n_pln, ft_lstnew(new_pln));
}

void	make_t_sphr(t_scn *nscn)
{
	t_sphr	*new_sphr;

	if (!(new_sphr = (t_sphr*)malloc(1 * sizeof(t_sphr))))
		new_sphr = NULL;
	new_sphr->p.x = 0;
	new_sphr->p.y = 0;
	new_sphr->p.z = 0;
	new_sphr->d = 0;
	new_sphr->r = 0;
	new_sphr->g = 0;
	new_sphr->b = 0;
	new_sphr->nxt = NULL;
	if (nscn->n_cntr.sphr == 0)
		nscn->n_sphr = ft_lstnew(new_sphr);
	else
		ft_lstadd_front(&nscn->n_sphr, ft_lstnew(new_sphr));
}

void	make_t_cyl(t_scn *nscn)
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
	new_cyl->r = 0;
	new_cyl->g = 0;
	new_cyl->b = 0;
	new_cyl->nxt = NULL;
	if (nscn->n_cntr.cyl == 0)
		nscn->n_cyl = ft_lstnew(new_cyl);
	else
		ft_lstadd_front(&nscn->n_cyl, ft_lstnew(new_cyl));
}

void	make_t_sqr(t_scn *nscn)
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
	new_sqr->r = 0;
	new_sqr->g = 0;
	new_sqr->b = 0;
	new_sqr->nxt = NULL;
	if (nscn->n_cntr.sqr == 0)
		nscn->n_sqr = ft_lstnew(new_sqr);
	else
		ft_lstadd_front(&nscn->n_sqr, ft_lstnew(new_sqr));
}

void	make_t_trngl(t_scn *nscn)
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
	new_trngl->r = 0;
	new_trngl->g = 0;
	new_trngl->b = 0;
	new_trngl->nxt = NULL;
	if (nscn->n_cntr.trngl == 0)
		nscn->n_trngl = ft_lstnew(new_trngl);
	else
		ft_lstadd_front(&nscn->n_trngl, ft_lstnew(new_trngl));
}

void	make_t_cntr(t_scn *nscn)
{
	nscn->n_cntr.cam = 0;
	nscn->n_cntr.lght = 0;
	nscn->n_cntr.pln = 0;
	nscn->n_cntr.sphr = 0;
	nscn->n_cntr.cyl = 0;
	nscn->n_cntr.sqr = 0;
	nscn->n_cntr.trngl = 0;
}

t_scn	*make_t_scn(void)
{
    t_scn   *nscn;

	if (!(nscn = (t_scn*)malloc(1 * sizeof(t_scn))))
		return (NULL);
	make_t_cntr(nscn);
	make_t_rsltn(nscn);
	make_t_ambnt(nscn);
	// make_t_cam(nscn);
	// make_t_lght(nscn);
	// make_t_pln(nscn);
	// make_t_sphr(nscn);
	// make_t_cyl(nscn);
	// make_t_sqr(nscn);
	// make_t_trngl(nscn);
	
	return (nscn);
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
	t_scn   *nscn;
	t_prsr  np;

	nscn = make_t_scn();
	np = make_t_prsr();

	prsr(scn_arr, size, nscn, &np);
	//rays_node(&nscn);
	//v_node();
	//print_node(nscn);
	lookat_node(nscn);
	
}

	//v_node();
	//cnvs_node(&nscn);
	//print_node(&nscn);
	//mlx_node();