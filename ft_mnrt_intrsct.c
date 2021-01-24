/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 22:27:23 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	sphr_intrsct(t_ray *ray, t_sphr *sphr)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	a;
	float	b;
	float	c;
	float	dscr;	//normalised vctr from the O(0,0,0) to some point on the viewport plane
	float	t1;
	float	t2;
	
	v_make(&oc, &ray->tail_p, &sphr->p);
	v_fill(&oc);
	printf("sphr.p.z:%f\n", sphr->p.z);
	a = v_d_prdct(&ray->vctr[ray->sgm].nxyz,&ray->vctr[ray->sgm].nxyz);
	b = 2 * v_d_prdct(&oc.xyz, &ray->vctr[ray->sgm].nxyz);
	c = v_d_prdct(&oc.xyz, &oc.xyz) - powf(sphr->d, 2);
	dscr = powf(b, 2) - 4 * a * c;
	printf("a:%f\n", a);
	printf("b:%f\n", b);
	printf("c:%f\n", c);
	printf("discriminant:%f\n", dscr);

	if (dscr == 0)
	{
		ray->dist = b / (2 * a);
		//ray->dist = t1;
		printf("t:%f\n", t1);
	}
	else if (dscr > 0)
	{
		t1 = (b + sqrtf(dscr)) / (2 * a);
		t2 = (b - sqrtf(dscr)) / (2 * a);
		if (t1 < t2)
			ray->dist = t1;
		else
			ray->dist = t2;
		printf("t1:%f\n", t1);
		printf("t2:%f\n", t2);
	}
	// else
	// 	ray->dist = INFINITY;
	printf("dist:%f\n", ray->dist);

	if (ray->dist > 0)
	{
		ray->r = sphr->r;
		ray->g = sphr->g;
		ray->b = sphr->b;
	}
}