/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_nrml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:28:48 by rburton           #+#    #+#             */
/*   Updated: 2021/01/30 22:01:18 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr)
{
    v_make(nrml, &sphr->p, &ray->hit_p[ray->sgm]);
}

void	nrml_pln_sqr(t_vctr *nrml, t_vxyz *xyz)
{
	v_null(nrml);
	nrml->xyz.x = xyz->x;
	nrml->xyz.y = xyz->y;
	nrml->xyz.z = xyz->z;
	v_fill(nrml);
}

void	nrml_trngl(t_trngl *trn)
{
	t_vctr	a;
	t_vctr	b;
	t_vctr	nrml;

	v_make(&a, &trn->p1, &trn->p2);
	v_make(&b, &trn->p1, &trn->p3);
	v_crss_prdct(&nrml.xyz, &a.xyz, &b.xyz);
	trn->n = nrml;
	v_fill(&trn->n);
	printf("vAB(%f, %f, %f)\n", a.xyz.x, a.xyz.y, a.xyz.z);
	printf("nvAB(%f, %f, %f)\n", a.nxyz.x, a.nxyz.y, a.nxyz.z);
	printf("vAC(%f, %f, %f)\n", b.xyz.x, b.xyz.y, b.xyz.z);
	printf("nvAC(%f, %f, %f)\n", b.nxyz.x, b.nxyz.y, b.nxyz.z);
}