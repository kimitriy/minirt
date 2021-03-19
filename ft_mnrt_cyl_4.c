/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:48:14 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 22:50:14 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	find_roots(t_cylon *cln, t_cyl *cyl, t_look_at *lkt)
{
	float	r;

	r = cyl->d / 2;
	cln->oh_p = sqrtf(powf(cln->v_o_c.lngth, 2) - powf(cln->ch_p, 2));
	cln->hxp_p = sqrtf(powf(r, 2) - powf(cln->ch_p, 2));
	if (cln->v_o_c.lngth <= r && cln->v_p_c.lngth <= r && cln->o_nb.z < 0)
		case1_2(cln, lkt);
	else if (cln->v_o_c.lngth <= r && cln->o_nb.z >= 0 && cln->o_nb.z <= cyl->h)
		case1_2(cln, lkt);
	else if (cln->v_o_c.lngth > r)
	{
		if (cln->angle < 90)
		{
			if (cln->ch_p < r)
				case3(cln);
			else if (cln->ch_p == r)
				case4(cln);
			else
				cylon_null(cln);
		}
		else if (cln->angle <= 90)
			cylon_null(cln);
	}
	else if (cln->v_o_c.lngth <= r && cln->v_p_c.lngth > r)
		cylon_null(cln);
}

void	cylon_make(t_cylon *cln, t_ray *ray, t_cyl *cyl)
{
	t_look_at	lkt;

	cylon_null(cln);
	cylon_fill(cln, ray, cyl);
	cap_pln(cln, cyl);
	look_at_mtrx(&lkt, &cyl->v, &cln->pln.p);
	pln_calc(cln);
	ch_calc(cln, &lkt);
	cln_angles(cln);
	find_roots(cln, cyl, &lkt);
	is_on_cyl(cln, cyl, &lkt);
	if ((cln->t1 != INFINITY || cln->t2 != INFINITY) && ray->sgm == 0)
	{
		if (ray->sgm == 0)
			calc_nrml_cyl(cln, cyl);
		nrml_cyl(cyl, ray);
	}
}

void	cyl_intrsct(t_scn *lscn, t_ray *ray, t_cyl *cyl, t_cylon *cln)
{
	cylon_make(cln, ray, cyl);
	if (min_2floats(cln->t1, cln->t2) < ray->dist && ray->sgm == 0)
	{
		ray->obj = 'c';
		ray->nrst = lscn->n_cyl;
		ray->dist = cln->t1;
		if (cln->t1 != INFINITY && cln->t2 == INFINITY)
			ray->dist = cln->t1;
		else if (cln->t1 == INFINITY && cln->t2 != INFINITY)
			ray->dist = cln->t2;
		else if (cln->t1 != INFINITY && cln->t2 != INFINITY)
			ray->dist = cln->t1 < cln->t2 ? cln->t1 : cln->t2;
		if (ray->dist == cln->t1)
		{
			v_copy(&ray->vctr[0], &cln->v_oxp1);
			p_copy(&ray->hit_p, &cln->xp1);
		}
		else
		{
			v_copy(&ray->vctr[0], &cln->v_oxp2);
			p_copy(&ray->hit_p, &cln->xp2);
		}
	}
}

void	check_cyls(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_cyl	*cyl;
	t_cylon	cln;

	i = 0;
	lscn->n_cyl = lscn->frst_cyl;
	while (i < lscn->n_cntr.cyl)
	{
		cyl = lscn->n_cyl->content;
		cyl_intrsct(lscn, ray, cyl, &cln);
		if (ray->sgm == 1 && ray->shdw != 'y' &&
			min_2floats(cln.t1, cln.t2) < ray->vctr[1].lngth)
			ray->shdw = 'y';
		if (lscn->n_cyl->next != NULL)
			lscn->n_cyl = lscn->n_cyl->next;
		i++;
	}
}
