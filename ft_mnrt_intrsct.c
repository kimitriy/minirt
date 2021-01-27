/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/27 16:44:20 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	q_equation(float *root, float a, float b, float c)
{
	float	dscr;
	float	r1;
	float	r2;

	dscr = powf(b, 2) - 4 * a * c;
	if (dscr == 0)
		*root = b / (2 * a);
	else if (dscr > 0)
	{
		r1 = (b + sqrtf(dscr)) / (2 * a);
		r2 = (b - sqrtf(dscr)) / (2 * a);
		if (r1 < r2)
			*root = r1;
		else
			*root = r2;
	}
	return (dscr);
}

float	sphr_intrsct(t_ray *ray, t_sphr *sphr)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	a;
	float	b;
	float	c;
	float	dscr;

	v_make(&oc, &ray->tail_p, &sphr->p);
	v_fill(&oc);
	a = v_d_prdct(&ray->vctr[ray->sgm].nxyz,&ray->vctr[ray->sgm].nxyz);
	b = 2 * v_d_prdct(&oc.xyz, &ray->vctr[ray->sgm].nxyz);
	c = v_d_prdct(&oc.xyz, &oc.xyz) - powf(sphr->d, 2);
	dscr = q_equation(&ray->dist[ray->sgm], a, b, c);
	if (dscr >= 0)
	{
		ray->obj = 's';
		v_n_prdct(&ray->vctr[ray->sgm].xyz, &ray->vctr[ray->sgm].nxyz, ray->dist[ray->sgm]);
		v_fill(&ray->vctr[ray->sgm]);
		p_calc(&ray->hit_p[ray->sgm], &ray->vctr[ray->sgm], &ray->tail_p);
	}
	return (dscr);
}

void 	check_sphrs(t_scn *lscn, t_ray *ray)
{
	int		i;
	float	dscr;
	t_sphr	*sphr;

	i = 0;
	lscn->n_sphr = lscn->frst_sphr;
	while (i < lscn->n_cntr.sphr)
	{
		sphr = lscn->n_sphr->content;
		dscr = sphr_intrsct(ray, sphr);
		if (dscr >= 0)
			lum_sphr(lscn, sphr, ray);
		if (lscn->n_sphr->next != NULL)
			lscn->n_sphr = lscn->n_sphr->next;
		i++;
	}
}

void	intrsct_node(t_scn *lscn, t_ray *ray)
{
	check_sphrs(lscn, ray);
	// check_plns(lscn, ray);
	// check_cyls(lscn, ray);
	// check_sqrs(lscn, ray);
	// check_trngls(lscn, ray);
}