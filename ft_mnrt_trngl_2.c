/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_trngl_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:20:24 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 18:21:12 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	is_in_trngl(t_trngl *trngl)
{
	float	r1;
	float	r2;
	int		i;

	i = 0;
	r1 = v2d_pd_prdct(&trngl->trgn._axp, &trngl->trgn._ab);
	r2 = v2d_pd_prdct(&trngl->trgn._ac, &trngl->trgn._ab);
	if (r1 <= 0 && r2 < 0)
		i++;
	r1 = v2d_pd_prdct(&trngl->trgn._bxp, &trngl->trgn._bc);
	r2 = v2d_pd_prdct(&trngl->trgn._ba, &trngl->trgn._bc);
	if (r1 <= 0 && r2 < 0)
		i++;
	r1 = v2d_pd_prdct(&trngl->trgn._cxp, &trngl->trgn._ca);
	r2 = v2d_pd_prdct(&trngl->trgn._cb, &trngl->trgn._ca);
	if (r1 <= 0 && r2 < 0)
		i++;
	if (i == 3)
		trngl->trgn.xp_in = '+';
}

void	trgn_make(t_trngl *trngl, t_ray *ray)
{
	nrml_make(trngl);
	look_at_mtrx(&trngl->trgn.lkt, &trngl->trgn.v_minus_f, &trngl->p1);
	nrml_trngl(trngl, ray);
	xp_calc(trngl, ray);
	trgn_converse(trngl);
	vctr2d_make(trngl);
	is_in_trngl(trngl);
}

void	trngl_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray)
{
	trgn_null(&trngl->trgn);
	trgn_make(trngl, ray);
	if (trngl->trgn.xp_in == '+' && trngl->trgn.t > 0 &&
		trngl->trgn.t <= ray->dist && ray->sgm == 0)
	{
		ray->dist = trngl->trgn.t;
		ray->obj = 't';
		ray->nrst = lscn->n_trngl;
		v_copy(&ray->vctr[0], &trngl->trgn.v_op);
		p_copy(&ray->hit_p, &trngl->trgn.xp);
	}
	if (trngl->trgn.xp_in == '+' && ray->sgm == 1 && trngl->trgn.t > 0.000147
		&& ray->shdw != 'y' && trngl->trgn.t < ray->vctr[1].lngth)
		ray->shdw = 'y';
}

void	check_trngls(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_trngl	*trngl;

	i = 0;
	lscn->n_trngl = lscn->frst_trngl;
	while (i < lscn->n_cntr.trngl)
	{
		trngl = lscn->n_trngl->content;
		trngl_intrsct(lscn, trngl, ray);
		if (lscn->n_trngl->next != NULL)
			lscn->n_trngl = lscn->n_trngl->next;
		i++;
	}
}
