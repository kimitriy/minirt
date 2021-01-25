/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/25 18:02:50 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	q_equation(float *root, float a, float b, float c)
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
}

void	sphr_intrsct(t_ray *ray, t_sphr *sphr)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	a;
	float	b;
	float	c;

	v_make(&oc, &ray->tail_p, &sphr->p);
	v_fill(&oc);
	a = v_d_prdct(&ray->vctr[ray->sgm].nxyz,&ray->vctr[ray->sgm].nxyz);
	b = 2 * v_d_prdct(&oc.xyz, &ray->vctr[ray->sgm].nxyz);
	c = v_d_prdct(&oc.xyz, &oc.xyz) - powf(sphr->d, 2);
	q_equation(&ray->dist[ray->sgm], a, b, c);
}