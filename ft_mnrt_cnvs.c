/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cnvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:17:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 22:47:47 by rburton          ###   ########.fr       */
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

// t_point	*cnvrse2xyz(t_scn *lscn, t_2d_point *xy)
// {
// 	t_cam	*tmp;
// 	t_point	*viewport_point;
// 	float	viewport_w;
// 	float	viewport_h;
// 	float	k;

// 	viewport_point = p_make(0, 0, 1);
// 	tmp = lscn->n_cam->content;
// 	viewport_w = 2 * tanf((tmp->fov * M_PI / 180) / 2);
// 	viewport_point->x = xy->x * (viewport_w / lscn->n_rsltn.x);
// 	k = (float)lscn->n_rsltn.y / (float)lscn->n_rsltn.x;
// 	viewport_h = viewport_w * k;
// 	viewport_point->y = xy->y * (viewport_h/(float)lscn->n_rsltn.y);
// 	return (viewport_point);
// }

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

// void	cnvs_node(t_scn *lscn)
// {
// 	t_point	new_point;
// 	t_2d_point a_ncrtsn;
// 	t_2d_point b_crtsn;

// 	a_ncrtsn.x = 1710;
// 	a_ncrtsn.y = 40;
// 	b_crtsn.y = 750;
// 	b_crtsn.y = 500;

// 	printf("a:(x:%d, y:%d)\n", a_ncrtsn.x, a_ncrtsn.y);
// 	printf("b:(x:%d, y:%d)\n", b_crtsn.x, b_crtsn.y);

// 	cnvrse2crtsn(lscn, &a_ncrtsn);
// 	cnvrse2ncrtsn(lscn, &b_crtsn);
// 	cnvrse2xyz(lscn, &new_point, &b_crtsn);
	
// 	printf("a:(x:%d, y:%d)\n", a_ncrtsn.x, a_ncrtsn.y);
// 	printf("b:(x:%d, y:%d)\n", b_crtsn.x, b_crtsn.y);
// 	printf("new_point:(x:%f, y:%f, z:%f)\n", new_point.x, new_point.y, new_point.z);
// }
