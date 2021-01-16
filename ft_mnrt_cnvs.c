/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cnvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:17:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/16 15:06:24 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cnvrse2crtsn(t_cnvs_xy *xy)
{
	xy->x_crtsn = xy->x_ncrtsn - xy->rsltn.x / 2;
	xy->y_crtsn = xy->rsltn.y / 2 - xy->y_ncrtsn;
}

void	cnvrse2ncrtsn(t_cnvs_xy *xy)
{
	xy->x_ncrtsn = xy->rsltn.x / 2 + xy->x_crtsn;
	xy->y_ncrtsn = xy->rsltn.y / 2 - xy->y_crtsn;
}

t_point	*cnvrse2xyz(t_scn *nscn, t_cnvs_xy *xy)
{
	t_cam	*tmp;
	t_point	*viewport_point;
	float	viewport_w;
	float	viewport_h;
	float	k;

	viewport_point = p_make(0, 0, 1);
	tmp = nscn->n_cam->content;
	viewport_w = 2 * tanf((tmp->fov * M_PI / 180) / 2);
	viewport_point->x = xy->x_crtsn * (viewport_w / xy->rsltn.x);
	k = (float)xy->rsltn.y / (float)xy->rsltn.x;
	viewport_h = viewport_w * k;
	viewport_point->y = xy->y_crtsn * (viewport_h/(float)xy->rsltn.y);
	return (viewport_point);
}

void	cnvs_node(t_scn *nscn)
{
	t_cnvs_xy	new_cnvs_xy1;
	t_cnvs_xy	new_cnvs_xy2;
	t_point		*new_point;

	new_cnvs_xy1.rsltn.x = nscn->n_rsltn.x;
	new_cnvs_xy2.rsltn.x = nscn->n_rsltn.x;
	new_cnvs_xy1.rsltn.y = nscn->n_rsltn.y;
	new_cnvs_xy2.rsltn.y = nscn->n_rsltn.y;
	new_cnvs_xy1.x_ncrtsn = 1710;
	new_cnvs_xy1.y_ncrtsn = 40;
	new_cnvs_xy2.x_crtsn = 750;
	new_cnvs_xy2.y_crtsn = 500;

	cnvrse2crtsn(&new_cnvs_xy1);
	cnvrse2ncrtsn(&new_cnvs_xy2);
	new_point = cnvrse2xyz(nscn, &new_cnvs_xy1);
	
	printf("new_cnvs_xy1:(x_ncrtsn:%d, y_ncrtsn:%d, x_crtsn:%d, y_crtsn:%d)\n", new_cnvs_xy1.x_ncrtsn, new_cnvs_xy1.y_ncrtsn, new_cnvs_xy1.x_crtsn, new_cnvs_xy1.y_crtsn);
	printf("new_cnvs_xy2:(x_crtsn:%d, y_crtsn:%d, x_ncrtsn:%d, y_ncrtsn:%d)\n", new_cnvs_xy2.x_crtsn, new_cnvs_xy2.y_crtsn, new_cnvs_xy2.x_ncrtsn, new_cnvs_xy2.y_ncrtsn);
	printf("new_point:(x:%f, y:%f, z:%f)\n", new_point->x, new_point->y, new_point->z);
}
