/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sphr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:42:55 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:38:33 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	q_equation(float *dscr, float a, float b, float c)
{
	float	r1;
	float	r2;
	float	root;

	root = INFINITY;
	*dscr = powf(b, 2) - 4 * a * c;
	if (dscr == 0)
		root = b / (2 * a);
	else if (dscr > 0)
	{
		r1 = (b + sqrtf(*dscr)) / (2 * a);
		r2 = (b - sqrtf(*dscr)) / (2 * a);
		if (r1 > 0 && r2 > 0)
		{
			if (r1 < r2)
				root = r1;
			else
				root = r2;
		}
		else if (r1 > 0 && r2 < 0)
			root = r1;
		else if (r2 > 0 && r1 < 0)
			root = r2;
	}
	return (root);
}

void	sphr_intrsct(t_scn *lscn, t_sphr *sphr, t_ray *ray)
{
	t_sphr_intrsct t;

	v_null(&t.oc);
	v_make(&t.oc, &ray->tail_p, &sphr->p);
	t.a = v_d_prdct(&ray->vctr[ray->sgm].nxyz, &ray->vctr[ray->sgm].nxyz);
	t.b = 2 * v_d_prdct(&t.oc.xyz, &ray->vctr[ray->sgm].nxyz);
	t.c = v_d_prdct(&t.oc.xyz, &t.oc.xyz) - powf(sphr->d / 2, 2);
	t.root = q_equation(&t.dscr, t.a, t.b, t.c) * 1.00001;
	if (t.dscr >= 0 && t.root < ray->dist && t.root > 0 && ray->sgm == 0)
	{
		ray->dist = t.root;
		ray->obj = 's';
		ray->nrst = lscn->n_sphr;
		v_n_prdct(&ray->vctr[0].xyz, &ray->vctr[0].nxyz, ray->dist);
		v_fill(&ray->vctr[0]);
		p_calc(&ray->hit_p, &ray->vctr[0].xyz, &ray->tail_p);
	}
	if (ray->sgm == 1 && t.dscr >= 0 && t.root > 0.01 &&
		t.root < ray->vctr[1].lngth && ray->shdw != 'y')
		ray->shdw = 'y';
}

void	check_sphrs(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_sphr	*sphr;

	i = 0;
	lscn->n_sphr = lscn->frst_sphr;
	while (i < lscn->n_cntr.sphr)
	{
		sphr = lscn->n_sphr->content;
		sphr_intrsct(lscn, sphr, ray);
		if (lscn->n_sphr->next != NULL)
			lscn->n_sphr = lscn->n_sphr->next;
		i++;
	}
}
