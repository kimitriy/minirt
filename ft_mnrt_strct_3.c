/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:57:54 by rburton           #+#    #+#             */
/*   Updated: 2021/03/22 15:04:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

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

t_scn	*make_t_scn(char save)
{
	t_scn	*scn;

	if (!(scn = (t_scn*)malloc(1 * sizeof(t_scn))))
		err_message("Memory allocation error.");
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
	if (save == '+')
		scn->save = save;
	return (scn);
}

void	nprsr_reset_counters(t_prsr *nprsr)
{
	nprsr->i = 0;
	nprsr->j = 0;
	nprsr->n = 0;
}

void	nprsr_null_4(t_prsr *nprsr)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		nprsr->r[i] = '\0';
		nprsr->g[i] = '\0';
		nprsr->b[i] = '\0';
		nprsr->fov[i] = '\0';
	}
}
