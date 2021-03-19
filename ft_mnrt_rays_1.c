/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:24:43 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void			trace_ray(t_scn *lscn, t_ray *ray)
{
	v_make(&ray->vctr[ray->sgm], &ray->tail_p, &ray->head_p);
	intrsct_node(lscn, ray);
}

void			ray_null(t_ray *ray)
{
	ray->sgm = 0;
	ray->obj = '\0';
	ray->shdw = '\0';
	p_make(&ray->tail_p, 0, 0, 0);
	p_make(&ray->head_p, 0, 0, 0);
	v_null(&ray->vctr[0]);
	v_null(&ray->vctr[1]);
	p_make(&ray->hit_p, 0, 0, 0);
	ray->dist = INFINITY;
	color_make(&ray->obj_trgb, '\0', '\0', '\0');
	color_make(&ray->sum_trgb, '\0', '\0', '\0');
	color_make(&ray->p_trgb, 7, 7, 7);
	ray->nrst = NULL;
}

unsigned long	cnvrse2trgb(t_color *trgb)
{
	return (((trgb->t & 0xff) << 24) + ((trgb->r & 0xff) << 16) +
		((trgb->g & 0xff) << 8) + (trgb->b & 0xff));
}

unsigned int	**make_rays_array(t_scn *lscn)
{
	unsigned int	y;
	unsigned int	**arr;

	y = 0;
	if (!(arr = (unsigned int**)malloc(lscn->n_rsltn.y *
		sizeof(unsigned int*))))
		return (NULL);
	while (y < lscn->n_rsltn.y)
	{
		if (!(arr[y] = (unsigned int*)malloc(lscn->n_rsltn.x *
			sizeof(unsigned int))))
			return (NULL);
		y++;
	}
	return (arr);
}

void			arr_ground_color(t_scn *lscn, unsigned int **rays_arr)
{
	unsigned int	x;
	unsigned int	y;
	t_color			clr;

	y = 0;
	x = 0;
	color_make(&clr, 0, 0, 0);
	while (y < lscn->n_rsltn.y)
	{
		while (x < lscn->n_rsltn.x)
		{
			rays_arr[y][x] = (unsigned int)cnvrse2trgb(&clr);
			x++;
		}
		x = 0;
		y++;
	}
}
