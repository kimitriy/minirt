/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/18 20:47:01 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	sphr_intrsct(t_ray *ray, t_sphr *sphr)
{
	t_vctr	oc;
	t_vctr	d;
	float	dscrmnnt;

	oc = *(v_make(ray->tail_point, sphr->p));
	dscrmnnt = powf(2 * v_dt_prdct(oc.xyz, ray->vctr->nrmlsd))
}