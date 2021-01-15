/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cnvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:17:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/15 17:21:54 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cnvrse2crtsn(t_scn *nscn, t_cnvs_xy *xy)
{
	xy->rsltn.x = nscn->n_rsltn.x;
	xy->rsltn.y = nscn->n_rsltn.y;
	xy->x_crtsn = xy->x_ncrtsn - xy->rsltn.x / 2;
	xy->y_crtsn = xy->rsltn.y / 2 - xy->y_ncrtsn;
}

void	cnvrse2ncrtsn(t_scn *nscn, t_cnvs_xy *xy)
{
	xy->rsltn.x = nscn->n_rsltn.x;
	xy->rsltn.y = nscn->n_rsltn.y;
	xy->x_ncrtsn = xy->rsltn.x / 2 + xy->x_crtsn;
	xy->y_ncrtsn = xy->rsltn.y / 2 - xy->y_crtsn;
}

t_point	*cnvrse2xyz(t_scn *nscn, t_cnvs_xy *xy)
{
	t_cam	*tmp;
	t_point	*viewport_point;

	viewport_point->x = xy->x_crtsn * (h14 / xy->rsltn.x);

	h14 = 2 * tanf(nscn->n_cam->content);

	return (viewport_point);
}