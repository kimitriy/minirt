/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:58:05 by rburton           #+#    #+#             */
/*   Updated: 2021/03/20 01:11:21 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	nprsr_null_6(t_prsr *nprsr)
{
	int		i;

	i = -1;
	while (++i < 6)
	{
		nprsr->rx[i] = '\0';
		nprsr->ry[i] = '\0';
	}
}

void	nprsr_null_42(t_prsr *nprsr)
{
	int		i;

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

void	nprsr_nullt_fields(t_prsr *nprsr)
{
	nprsr_null_4(nprsr);
	nprsr_null_6(nprsr);
	nprsr_null_42(nprsr);
}

t_prsr	make_t_prsr(void)
{
	t_prsr	nprsr;

	nprsr_reset_counters(&nprsr);
	nprsr_nullt_fields(&nprsr);
	return (nprsr);
}

void	strct_node(char **scn_arr, int size, char save)
{
	t_scn	*scn;
	t_prsr	np;

	scn = make_t_scn(save);
	np = make_t_prsr();
	prsr(scn_arr, size, scn, &np);
	lookat_node(scn, 0);
}
