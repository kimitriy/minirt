/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 02:18:41 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

// void	ray_eqtn(t_ray *ray, int dstnce, int gen)
// {
// 	int		i;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		ray->hit_point[i].x = 0;
// 		ray->hit_point[i].y = 0;
// 		ray->hit_point[i].z = 0;
// 		i++;
// 	}
// 	ray->vctr[0] = *(v_make(&ray->tail_point, &ray->head_point)); 
// 	ray->dstnce = dstnce;
// 	nv_n_prdct(ray->vctr, ray->dstnce);
// 	ray->hit_point[gen] = *p_make(ray->vctr->x + ray->tail_point.x, ray->vctr->y + ray->tail_point.y, ray->vctr->z + ray->tail_point.z);
// }

void	trace_ray_segment(t_ray *ray, t_scn *lscn)
{
	t_sphr	*tmp;

	tmp = lscn->n_sphr->content;
	sphr_intrsct(ray, tmp);
	if (ray->dst != 0)
	{
		ray->r = tmp->r;
		ray->g = tmp->g;
		ray->b = tmp->b;
	}
}

void	trace_ray(t_scn *lscn, t_ray *ray, t_2d_point *xy)
{
	cnvrse2crtsn(lscn, xy);
    cnvrse2xyz(&ray->hd_p, lscn, xy);
	while (ray->s < 1) //3
	{
		if (ray->s == 0)
		{	
			v_make(&ray->v[ray->s], &ray->tl_p, &ray->hd_p);
			trace_ray_segment(ray, lscn);
		
			// ray->r = 0;
			// ray->g = 0;
			// ray->b = 255;
		}
		// else
		// {
		// 	//func that calculates reflected vctr
		// }
		//trace_ray_segment(ray, lscn);
		ray->s++;
	}
	//printf("ray(tail(%f, %f, %f), head(%f, %f, %f), vctr(%f, %f, %f), length:%f, nrmlsd(%f, %f, %f), dstnc:%f, h_point(%f, %f, %f))\n", nray->tail_point->x, nray->tail_point->y, nray->tail_point->z, nray->head_point->x, nray->head_point->y, nray->head_point->z, nray->vctr->x, nray->vctr->y, nray->vctr->z, nray->vctr->lngth, nray->vctr->nx, nray->vctr->ny, nray->vctr->nz, nray->dstnce, nray->hit_point[0].x, nray->hit_point[0].y, nray->hit_point[0].z);
}

void	ray_null(t_ray *ray)
{
	ray->s = 0;
	p_make(&ray->tl_p, 0, 0, 0);
	p_make(&ray->hd_p, 0, 0, 0);
	v_null(&ray->v[0]);
	v_null(&ray->v[1]);
	v_null(&ray->v[2]);
	p_make(&ray->hit_p[0], 0, 0, 0);
	p_make(&ray->hit_p[1], 0, 0, 0);
	p_make(&ray->hit_p[2], 0, 0, 0);
	ray->dst = 0;
	ray->a = 0;
	ray->r = 0;
	ray->g = 0;
	ray->b = 0;
}

unsigned long cnvrse2argb(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
{   
	return (((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

unsigned int	**make_rays_array(t_scn *lscn)
{
	unsigned int 	x;
	unsigned int	y;
	unsigned int	**arr;

	y = 0;
	if (!(arr = (unsigned int**)malloc(lscn->n_rsltn.y * sizeof(unsigned int*))))
		return (NULL);
	while (y < lscn->n_rsltn.y)
	{
		if (!(arr[y] = (unsigned int*)malloc(lscn->n_rsltn.x * sizeof(unsigned int))))
			return (NULL);
		y++;
	}
	y = 0;
	x = 0;
	while (y < lscn->n_rsltn.y)
	{
		while (x < lscn->n_rsltn.x)
		{
			arr[y][x] = (unsigned int)cnvrse2argb(0, 0, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
	return (arr);
}

void	launch_rays(t_scn *lscn, unsigned int **rays_arr)
{
	int			x;
	int			y;
	t_2d_point	xy;
	t_ray		ray;

	ray_null(&ray);
	x = 0;
	y = 0;
	while (y < lscn->n_rsltn.y)
	{
		while (x < lscn->n_rsltn.x)
		{
			p2d_make(&xy, x, y);
			trace_ray(lscn, &ray, &xy);
			rays_arr[y][x] = (unsigned int)cnvrse2argb(ray.a, ray.r, ray.g, ray.b);
			x++;
		}
		x = 0;
		y++;
	}
}

void	rays_node(t_scn *lscn)
{
	unsigned int	**rays_arr;
	
	rays_arr = make_rays_array(lscn);
	launch_rays(lscn, rays_arr);
	img2win(lscn, rays_arr);
}