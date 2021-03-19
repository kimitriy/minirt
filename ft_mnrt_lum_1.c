/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lum_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:16:42 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 13:00:34 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	l_ambnt(t_lum *lum)
{
	const float pi = 3.141593;
	float		beta;

	beta = v_angle(&lum->op, &lum->nrml) * 180 / pi;
	lum->angl = 180 - beta;
	lum->ka = (lum->angl >= 0 && lum->angl < 90) ?
		cos(lum->angl * pi / 180) : 0;
	lum->la = lum->alvl * lum->ka;
}

void	l_dffse(t_lum *lum)
{
	float	fade;
	float	mx;

	lum->kd = 30;
	fade = lum->lvl / powf(lum->dst, 2);
	mx = max_2floats(0, v_d_prdct(&lum->ldir.nxyz, &lum->nrml.nxyz));
	lum->ld = lum->kd * fade * mx;
}

void	l_spclr(t_lum *lum)
{
	float	fade;
	float	mx;

	lum->ks = 30;
	lum->p = 64;
	fade = lum->lvl / powf(lum->dst, 2);
	mx = max_2floats(0, v_d_prdct(&lum->nrml.nxyz, &lum->hvctr.nxyz));
	lum->ls = lum->ks * fade * powf(mx, lum->p);
}

void	l_all(t_scn *lscn, t_lum *lum)
{
	if (lum->shdw == 'y' || lscn->n_cntr.lght == 0)
	{
		l_ambnt(lum);
		lum->ld = 0;
		lum->ls = 0;
	}
	else
	{
		l_ambnt(lum);
		l_dffse(lum);
		l_spclr(lum);
	}
	lum->l = lum->la + lum->ld + lum->ls;
	lum->l = lum->l >= 1 ? 1 : lum->l;
}
