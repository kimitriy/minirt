/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/25 18:02:06 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"


void	trace_ray_segment(t_ray *ray, t_scn *lscn)
{
	t_sphr	*tmp;

	tmp = lscn->n_sphr->content;
	sphr_intrsct(ray, tmp);
	if (ray->dist[ray->sgm] > 0)
	{
		ray->r = tmp->r;
		ray->g = tmp->g;
		ray->b = tmp->b;
	}
}

void	trace_ray(t_scn *lscn, t_ray *ray, t_2d_point *xy)
{
	cnvrse2crtsn(lscn, xy);
    cnvrse2xyz(&ray->head_p, lscn, xy);
	while (ray->sgm < 1) //3
	{
		if (ray->sgm == 0)
		{	
			v_make(&ray->vctr[ray->sgm], &ray->tail_p, &ray->head_p);
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
		ray->sgm++;
	}
}

void	ray_null(t_ray *ray)
{
	ray->sgm = 0;
	p_make(&ray->tail_p, 0, 0, 0);
	p_make(&ray->head_p, 0, 0, 0);
	v_null(&ray->vctr[0]);
	v_null(&ray->vctr[1]);
	v_null(&ray->vctr[2]);
	p_make(&ray->hit_p[0], 0, 0, 0);
	p_make(&ray->hit_p[1], 0, 0, 0);
	p_make(&ray->hit_p[2], 0, 0, 0);
	ray->dist[0] = 0;
	ray->dist[1] = 0;
	ray->dist[2] = 0;
	ray->a = 100;
	ray->r = 100;
	ray->g = 100;
	ray->b = 100;
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
	// y = 0;
	// x = 0;
	// while (y < lscn->n_rsltn.y)
	// {
	// 	while (x < lscn->n_rsltn.x)
	// 	{
	// 		arr[y][x] = (unsigned int)cnvrse2argb(100, 100, 100, 100);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
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
			// x = 250;
			// y = 250;
			p2d_make(&xy, x, y);
			trace_ray(lscn, &ray, &xy);
			rays_arr[y][x] = (unsigned int)cnvrse2argb(ray.a, ray.r, ray.g, ray.b);
			ray.sgm = 0;
			ray_null(&ray);
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