/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lum_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:59:36 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 13:00:40 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	lum_sqr(t_scn *lscn, t_lght *lght, t_ray *ray)
{
	t_lum	lum;
	t_sqr	*sqr;

	sqr = ray->nrst->content;
	ray->sgm = 0;
	nrml_sqr(sqr, ray);
	v_copy(&lum.nrml, &sqr->v);
	v_fill(&lum.nrml);
	make_lum(&lum, lscn, lght, ray);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &sqr->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_cyl(t_scn *lscn, t_lght *lght, t_ray *ray)
{
	t_lum	lum;
	t_cyl	*cyl;

	cyl = ray->nrst->content;
	ray->sgm = 0;
	nrml_cyl(cyl, ray);
	v_copy(&lum.nrml, &cyl->n);
	v_fill(&lum.nrml);
	make_lum(&lum, lscn, lght, ray);
	l_all(lscn, &lum);
	color_copy(&ray->obj_trgb, &cyl->trgb);
	color_node(lscn, ray, &lum);
}

void	lum_node(t_scn *lscn, t_lght *lght, t_ray *ray)
{
	if (ray->obj == 's')
		lum_sphr(lscn, lght, ray);
	if (ray->obj == 'p')
		lum_pln(lscn, lght, ray);
	if (ray->obj == 't')
		lum_trngl(lscn, lght, ray);
	if (ray->obj == 'q')
		lum_sqr(lscn, lght, ray);
	if (ray->obj == 'c')
		lum_cyl(lscn, lght, ray);
}
