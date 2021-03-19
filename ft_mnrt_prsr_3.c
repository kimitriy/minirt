/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:05:52 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:09:01 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	write_pln(t_scn *nscn, t_prsr *np)
{
	t_pln *tmp;

	check_values_node(np, 'p');
	tmp = NULL;
	make_t_pln(nscn);
	if (nscn->n_cntr.pln == 0)
		nscn->frst_pln = nscn->n_pln;
	if (nscn->n_pln->next != NULL)
		nscn->n_pln = nscn->n_pln->next;
	tmp = nscn->n_pln->content;
	write_p(&tmp->p, np);
	write_v(&tmp->v, np);
	write_color(&tmp->trgb, np);
	nscn->n_cntr.pln++;
}

void	write_sphr(t_scn *nscn, t_prsr *np)
{
	t_sphr *tmp;

	check_values_node(np, 's');
	make_t_sphr(nscn);
	if (nscn->n_cntr.sphr == 0)
		nscn->frst_sphr = nscn->n_sphr;
	if (nscn->n_sphr->next != NULL)
		nscn->n_sphr = nscn->n_sphr->next;
	tmp = nscn->n_sphr->content;
	write_p(&tmp->p, np);
	tmp->d = ft_atof(np->d);
	write_color(&tmp->trgb, np);
	nscn->n_cntr.sphr++;
}

void	write_cyl(t_scn *nscn, t_prsr *np)
{
	t_cyl *tmp;

	check_values_node(np, 'c');
	make_t_cyl(nscn);
	if (nscn->n_cntr.cyl == 0)
		nscn->frst_cyl = nscn->n_cyl;
	if (nscn->n_cyl->next != NULL)
		nscn->n_cyl = nscn->n_cyl->next;
	tmp = nscn->n_cyl->content;
	write_p(&tmp->p, np);
	write_v(&tmp->v, np);
	tmp->d = ft_atof(np->d);
	tmp->h = ft_atof(np->h);
	write_color(&tmp->trgb, np);
	nscn->n_cntr.cyl++;
}

void	write_sqr(t_scn *nscn, t_prsr *np)
{
	t_sqr *tmp;

	check_values_node(np, 'q');
	make_t_sqr(nscn);
	if (nscn->n_cntr.sqr == 0)
		nscn->frst_sqr = nscn->n_sqr;
	if (nscn->n_sqr->next != NULL)
		nscn->n_sqr = nscn->n_sqr->next;
	tmp = nscn->n_sqr->content;
	write_p(&tmp->p, np);
	write_v(&tmp->v, np);
	tmp->v_tmp.xyz.x = 0;
	tmp->v_tmp.xyz.y = 1;
	tmp->v_tmp.xyz.z = 0;
	v_fill(&tmp->v_tmp);
	tmp->side = ft_atof(np->side);
	write_color(&tmp->trgb, np);
	nscn->n_cntr.sqr++;
}

void	write_trngl(t_scn *nscn, t_prsr *np)
{
	t_trngl *tmp;

	check_values_node(np, 't');
	make_t_trngl(nscn);
	if (nscn->n_cntr.trngl == 0)
		nscn->frst_trngl = nscn->n_trngl;
	if (nscn->n_trngl->next != NULL)
		nscn->n_trngl = nscn->n_trngl->next;
	tmp = nscn->n_trngl->content;
	write_p(&tmp->p1, np);
	tmp->p2.x = ft_atof(np->x2);
	tmp->p2.y = ft_atof(np->y2);
	tmp->p2.z = ft_atof(np->z2);
	tmp->p3.x = ft_atof(np->x3);
	tmp->p3.y = ft_atof(np->y3);
	tmp->p3.z = ft_atof(np->z3);
	write_color(&tmp->trgb, np);
	nscn->n_cntr.trngl++;
}
