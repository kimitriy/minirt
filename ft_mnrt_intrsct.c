/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 02:11:26 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	sphr_intrsct(t_ray *r, t_sphr *s)
{
	t_vctr	oc; //vctr from the O(0,0,0) to the C(x,y,z), that is the center of the sphr
	float	dscr;	//normalised vctr from the O(0,0,0) to some point on the viewport plane
	float	t1;
	float	t2;
	
	v_make(&oc, &r->tl_p, &s->p);
	v_fill(&oc);
	//d = r->vctr[r->sgmnt];
	dscr = powf(2 * v_d_prdct(&oc.nxyz, &r->v[r->s].nxyz), 2) - 4 * v_d_prdct(&r->v[r->s].nxyz, &r->v[r->s].nxyz) * (v_d_prdct(&oc.nxyz, &oc.nxyz) - powf(s->r, 2));
	if (dscr == 0)
	{
		t1 = (-1) * ((2 * v_d_prdct(&oc.nxyz, &r->v[r->s].nxyz)) / (2 * v_d_prdct(&r->v[r->s].nxyz, &r->v[r->s].nxyz)));
		r->dst = t1;
	}
	else if (dscr > 0)
	{
		t1 = (-1) * ((2 * v_d_prdct(&oc.nxyz, &r->v[r->s].nxyz) + sqrtf(dscr)) / (2 * v_d_prdct(&r->v[r->s].nxyz, &r->v[r->s].nxyz)));
		t2 = (-1) * ((2 * v_d_prdct(&oc.nxyz, &r->v[r->s].nxyz) - sqrtf(dscr)) / (2 * v_d_prdct(&r->v[r->s].nxyz, &r->v[r->s].nxyz)));
		if (t1 < t2)
			r->dst = t1;
		else
			r->dst = t2;
	}
}