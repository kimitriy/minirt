/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cnvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:17:03 by rburton           #+#    #+#             */
/*   Updated: 2021/03/17 01:20:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cnvrse2crtsn(t_scn *lscn, t_2d_point *xy)
{
	xy->x = xy->x - lscn->n_rsltn.x / 2;
	xy->y = lscn->n_rsltn.y / 2 - xy->y;
}


void	cnvrse2ncrtsn(t_scn *lscn, t_2d_point *xy)
{
	xy->x = lscn->n_rsltn.x / 2 + xy->x;
	xy->y = lscn->n_rsltn.y / 2 - xy->y;
}

void	cnvrse2xyz(t_point *out, t_scn *lscn, t_2d_point *xy)
{
	t_cam	*cam;
	float	viewport_w;
	float	viewport_h;
	float	k;

	p_make(out, 0, 0, 1);
	cam = lscn->n_cam->content;
	viewport_w = 2 * tanf((cam->fov * M_PI / 180) / 2);
	out->x = xy->x * (viewport_w / lscn->n_rsltn.x);
	k = (float)lscn->n_rsltn.y / (float)lscn->n_rsltn.x;
	viewport_h = viewport_w * k;
	out->y = xy->y * (viewport_h/(float)lscn->n_rsltn.y);
}
