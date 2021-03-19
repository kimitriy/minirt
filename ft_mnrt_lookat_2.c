/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lookat_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:44:26 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 20:22:25 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cnvrse_lght(t_scn *nscn, t_scn *lscn, t_look_at *lookat)
{
	t_lght	*lght;
	t_lght	*llght;

	nscn->n_lght = nscn->frst_lght;
	while (lscn->n_cntr.lght < nscn->n_cntr.lght)
	{
		make_t_lght(lscn);
		if (lscn->n_cntr.lght == 0)
			lscn->frst_lght = lscn->n_lght;
		if (lscn->n_lght->next != NULL)
			lscn->n_lght = lscn->n_lght->next;
		lght = nscn->n_lght->content;
		llght = lscn->n_lght->content;
		color_copy(&llght->trgb, &lght->trgb);
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
		color_copy(&lpln->trgb, &pln->trgb);
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
		lsphr->d = sphr->d;
		color_copy(&lsphr->trgb, &sphr->trgb);
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
		lcyl->h = cyl->h;
		lcyl->d = cyl->d;
		color_copy(&lcyl->trgb, &cyl->trgb);
		mtrx4_x_point(&lcyl->p, &lookat->m, &cyl->p);
		mtrx4_x_vctr(&lcyl->v, &lookat->m, &cyl->v.nxyz);
		v_fill(&lcyl->v);
		if (nscn->n_cyl->next != NULL)
			nscn->n_cyl = nscn->n_cyl->next;
		lscn->n_cntr.cyl++;
	}
}
