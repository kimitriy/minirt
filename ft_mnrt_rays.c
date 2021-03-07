/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/03/07 05:22:23 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	trace_ray(t_scn *lscn, t_ray *ray)
{
	v_make(&ray->vctr[ray->sgm], &ray->tail_p, &ray->head_p);
	intrsct_node(lscn, ray);
}

void	ray_null(t_ray *ray)
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

unsigned long cnvrse2trgb(t_color *trgb)
{   
	return (((trgb->t & 0xff) << 24) + ((trgb->r & 0xff) << 16) + ((trgb->g & 0xff) << 8) + (trgb->b & 0xff));
}

unsigned int	**make_rays_array(t_scn *lscn)
{
	unsigned int 	x;
	unsigned int	y;
	unsigned int	**arr;
	t_color			grey;

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
	color_make(&grey, 255, 255, 255);
	while (y < lscn->n_rsltn.y)
	{
		while (x < lscn->n_rsltn.x)
		{
			arr[y][x] = (unsigned int)cnvrse2trgb(&grey);
			x++;
		}
		x = 0;
		y++;
	}
	return (arr);
}

void	launch_rays(t_scn *lscn, unsigned int **rays_arr, t_ray *ray)
{
	unsigned int	x;
	unsigned int	y;
	t_2d_point		xy;
	
	// x = 0;
	// y = 0;
	// while (y < lscn->n_rsltn.y)
	// {
	// 	while (x < lscn->n_rsltn.x)
	// 	{
	// 		p2d_make(&xy, x, y);
	// 		cnvrse2crtsn(lscn, &xy);
    // 		cnvrse2xyz(&ray->head_p, lscn, &xy);
	// 		trace_ray(lscn, ray);
	// 		rays_arr[y][x] = (unsigned int)cnvrse2trgb(&ray->p_trgb);
	// 		ray_null(ray);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	
	// x = 500;
	// y = 460;	sqr upper fantom
	// y = 625; sqr bottom
	// y = 800; shadow
	
	x = 500;
	y = 535;
	p2d_make(&xy, x, y);
	cnvrse2crtsn(lscn, &xy);
	cnvrse2xyz(&ray->head_p, lscn, &xy);
	trace_ray(lscn, ray);
	rays_arr[y][x] = (unsigned int)cnvrse2trgb(&ray->p_trgb);
	ray_null(ray);

	// x = 395;
	// y = 606;
	
	// x = 487;
	// y = 628;
	// while (y <= 630)
	// {
	// 	while (x <= 515)
	// 	{
	// 		p2d_make(&xy, x, y);
	// 		cnvrse2crtsn(lscn, &xy);
    // 		cnvrse2xyz(&ray->head_p, lscn, &xy);
	// 		trace_ray(lscn, ray);
	// 		rays_arr[y][x] = (unsigned int)cnvrse2trgb(&ray->p_trgb);
	// 		ray_null(ray);
	// 		x++;
	// 	}
	// 	x = 487;
	// 	y++;
	// }
}

void	rays_node(t_scn *lscn, t_scn *nscn)
{
	unsigned int	**rays_arr;
	t_ray			ray;
	
	rays_arr = make_rays_array(lscn);
	ray_null(&ray);
	launch_rays(lscn, rays_arr, &ray);
	mlx_node(nscn, rays_arr);
}