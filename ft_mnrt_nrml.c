/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_nrml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:28:48 by rburton           #+#    #+#             */
/*   Updated: 2021/02/07 03:05:42 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void    nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr)
{
    v_make(nrml, &sphr->p, &ray->hit_p);
}

void	nrml_pln_sqr(t_vctr *nrml, t_vxyz *xyz)
{
	v_null(nrml);
	nrml->xyz.x = xyz->x;
	nrml->xyz.y = xyz->y;
	nrml->xyz.z = xyz->z;
	v_fill(nrml);
}

void	nrml_trngl(t_polygon *plgn, t_trngl *trn)
{
	t_vctr	ca;
	t_vctr	ab;
	t_vctr	nrml;

	v_make(&plgn->cd_a, &plgn->c, &plgn->a);
	v_make(&plgn->a_b, &plgn->a, &plgn->b);
	v_crss_prdct(&trn->n.xyz, &plgn->cd_a.xyz, &plgn->a_b.xyz);
	v_fill(&trn->n);
	// printf("vCA(%f, %f, %f), nvCA(%f, %f, %f)\n", ca.xyz.x, ca.xyz.y, ca.xyz.z, ca.nxyz.x, ca.nxyz.y, ca.nxyz.z);
	// printf("vAB(%f, %f, %f), nvAB(%f, %f, %f)\n", ab.xyz.x, ab.xyz.y, ab.xyz.z, ab.nxyz.x, ab.nxyz.y, ab.nxyz.z);
	// printf("N(%f, %f, %f)\n", trn->n.nxyz.x, trn->n.nxyz.y, trn->n.nxyz.z);
}