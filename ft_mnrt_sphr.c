/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_sphr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:42:55 by rburton           #+#    #+#             */
/*   Updated: 2021/03/09 14:41:08 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

float	q_equation(float *dscr, float a, float b, float c)
{
	float	r1;
	float	r2;
	float	root;

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
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	a;
	float	b;
	float	c;
	float	dscr;
	float	root;
	
	v_null(&oc);
	v_make(&oc, &ray->tail_p, &sphr->p);
	a = v_d_prdct(&ray->vctr[ray->sgm].nxyz,&ray->vctr[ray->sgm].nxyz);
	b = 2 * v_d_prdct(&oc.xyz, &ray->vctr[ray->sgm].nxyz);
	c = v_d_prdct(&oc.xyz, &oc.xyz) - powf(sphr->d / 2, 2);
	root = q_equation(&dscr, a, b, c) * 1.00001;
	if (dscr >= 0 && root < ray->dist && root > 0 && ray->sgm == 0)
	{
		ray->dist = root;
		ray->obj = 's';
		ray->nrst = lscn->n_sphr;
		v_n_prdct(&ray->vctr[0].xyz, &ray->vctr[0].nxyz, ray->dist); //makes a ray from the cam point to the intersection point
		v_fill(&ray->vctr[0]);
		p_calc(&ray->hit_p, &ray->vctr[0].xyz, &ray->tail_p); //calculates the hit point
	}
	if (ray->sgm == 1 && dscr >= 0 && root > 0.01 && root < ray->vctr[1].lngth && ray->shdw != 'y')
		ray->shdw = 'y';
}

void 	check_sphrs(t_scn *lscn, t_ray *ray)
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