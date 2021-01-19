/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cnvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:17:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/18 20:47:07 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cnvrse2crtsn(t_scn *nscn, t_2d_point *xy)
{
	xy->x = xy->x - nscn->n_rsltn.x / 2;
	xy->y = nscn->n_rsltn.y / 2 - xy->y;
}


void	cnvrse2ncrtsn(t_scn *nscn, t_2d_point *xy)
{
	xy->x = nscn->n_rsltn.x / 2 + xy->x;
	xy->y = nscn->n_rsltn.y / 2 - xy->y;
}

// t_point	*cnvrse2xyz(t_scn *nscn, t_2d_point *xy)
// {
// 	t_cam	*tmp;
// 	t_point	*viewport_point;
// 	float	viewport_w;
// 	float	viewport_h;
// 	float	k;

// 	viewport_point = p_make(0, 0, 1);
// 	tmp = nscn->n_cam->content;
// 	viewport_w = 2 * tanf((tmp->fov * M_PI / 180) / 2);
// 	viewport_point->x = xy->x * (viewport_w / nscn->n_rsltn.x);
// 	k = (float)nscn->n_rsltn.y / (float)nscn->n_rsltn.x;
// 	viewport_h = viewport_w * k;
// 	viewport_point->y = xy->y * (viewport_h/(float)nscn->n_rsltn.y);
// 	return (viewport_point);
// }

void	cnvrse2xyz(t_scn *nscn, t_point *output, t_2d_point *xy)
{
	t_cam	*tmp;
	float	viewport_w;
	float	viewport_h;
	float	k;

	p_make(output, 0, 0, 1);
	tmp = nscn->n_cam->content;
	viewport_w = 2 * tanf((tmp->fov * M_PI / 180) / 2);
	output->x = xy->x * (viewport_w / nscn->n_rsltn.x);
	k = (float)nscn->n_rsltn.y / (float)nscn->n_rsltn.x;
	viewport_h = viewport_w * k;
	output->y = xy->y * (viewport_h/(float)nscn->n_rsltn.y);
}

void	cnvs_node(t_scn *nscn)
{
	t_point	*new_point;
	t_2d_point a_ncrtsn;
	t_2d_point b_crtsn;

	a_ncrtsn.x = 1710;
	a_ncrtsn.y = 40;
	b_crtsn.y = 750;
	b_crtsn.y = 500;

	printf("a:(x:%d, y:%d)\n", a_ncrtsn.x, a_ncrtsn.y);
	printf("b:(x:%d, y:%d)\n", b_crtsn.x, b_crtsn.y);

	cnvrse2crtsn(nscn, &a_ncrtsn);
	cnvrse2ncrtsn(nscn, &b_crtsn);
	new_point = cnvrse2xyz(nscn, &b_crtsn);
	
	printf("a:(x:%d, y:%d)\n", a_ncrtsn.x, a_ncrtsn.y);
	printf("b:(x:%d, y:%d)\n", b_crtsn.x, b_crtsn.y);
	printf("new_point:(x:%f, y:%f, z:%f)\n", new_point->x, new_point->y, new_point->z);
}
