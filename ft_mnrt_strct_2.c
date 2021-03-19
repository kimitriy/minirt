/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:57:49 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 18:02:24 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

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
	v_null(&new_cyl->v);
	v_null(&new_cyl->n);
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
