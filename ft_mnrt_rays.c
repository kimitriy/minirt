/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/02/03 18:51:43 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	trace_ray(t_scn *lscn, t_ray *ray)
{
	// cnvrse2crtsn(lscn, xy);
    // cnvrse2xyz(&ray->head_p, lscn, xy);
	v_make(&ray->vctr[ray->sgm], &ray->tail_p, &ray->head_p);
	intrsct_node(lscn, ray);
	
	// while (ray->sgm < 1) //2
	// {
	// 	if (ray->sgm == 0)
	// 	{	
	// 		v_make(&ray->vctr[ray->sgm], &ray->tail_p, &ray->head_p);
	// 		trace_ray_segment(ray, lscn);
		
	// 		// ray->r = 0;
	// 		// ray->g = 0;
	// 		// ray->b = 255;
	// 	}
	// 	// else
	// 	// {
	// 	// 	//func that calculates reflected vctr
	// 	// }
	// 	//trace_ray_segment(ray, lscn);
	// 	ray->sgm++;
	// }
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
	color_make(&ray->p_trgb, 0, 0, 0);
	// ray->obj_trgb.t = '\0';
	// ray->obj_trgb.r = '\0';
	// ray->obj_trgb.g = '\0';
	// ray->obj_trgb.b = '\0';
	// ray->sum_trgb.t = '\0';
	// ray->sum_trgb.r = '\0';
	// ray->sum_trgb.g = '\0';
	// ray->sum_trgb.b = '\0';
	// ray->p_trgb.t = 100;
	// ray->p_trgb.r = 100;
	// ray->p_trgb.g = 100;
	// ray->p_trgb.b = 100;
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
	color_make(&grey, 100, 100, 100);
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
	
	x = 0;
	y = 0;
	while (y < lscn->n_rsltn.y)
	{
		while (x < lscn->n_rsltn.x)
		{
			p2d_make(&xy, x, y);
			cnvrse2crtsn(lscn, &xy);
    		cnvrse2xyz(&ray->head_p, lscn, &xy);
			trace_ray(lscn, ray);
			rays_arr[y][x] = (unsigned int)cnvrse2trgb(&ray->p_trgb);
			ray_null(ray);
			x++;
		}
		x = 0;
		y++;
	}
	
	//x1240y640 shadow on the blue sphr from the left light
	//x280y810 shadow on the pln from the right lght and white sphr
	//x480y860 shadow on the pln from the right lght and green sphr
	//x1440y860 shadow on the pln from the left lght and green sphr
	
	// x = 960;
	// y = 540;
	// p2d_make(&xy, x, y);
	// cnvrse2crtsn(lscn, &xy);
	// cnvrse2xyz(&ray->head_p, lscn, &xy);
	// trace_ray(lscn, ray);
	// rays_arr[y][x] = (unsigned int)cnvrse2trgb(&ray->p_trgb);
	// ray_null(ray);
	
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