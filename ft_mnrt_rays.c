/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/18 20:47:02 by rburton          ###   ########.fr       */
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

void	trace_ray_segment(t_ray *ray, t_scn *nscn)
{
	ray->dstnce = sphr_intrsct(ray, nscn->n_sphr);
}

t_ray	*trace_ray(t_scn *nscn, int x, int y, int z)
{
    t_ray		*new_ray;
	t_2d_point	xy;
	int			r;

    if (!(new_ray = (t_ray*)malloc(1 * sizeof(t_ray))))
		new_ray = NULL;
	xy.x = x;
	xy.y = y;
	cnvrse2crtsn(nscn, &xy);
    p_make(&new_ray->tail_point, 0, 0, 0);
    cnvrse2xyz(nscn, &new_ray->head_point, &xy);
	r = 0;
	while (r < 3)
	{
		//
		trace_ray_segment(new_ray, nscn);
		r++;
	}
	//printf("ray(tail(%f, %f, %f), head(%f, %f, %f), vctr(%f, %f, %f), length:%f, nrmlsd(%f, %f, %f), dstnc:%f, h_point(%f, %f, %f))\n", nray->tail_point->x, nray->tail_point->y, nray->tail_point->z, nray->head_point->x, nray->head_point->y, nray->head_point->z, nray->vctr->x, nray->vctr->y, nray->vctr->z, nray->vctr->lngth, nray->vctr->nx, nray->vctr->ny, nray->vctr->nz, nray->dstnce, nray->hit_point[0].x, nray->hit_point[0].y, nray->hit_point[0].z);
    return (new_ray);
}

unsigned long cnvrse2argb(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
{   
	return (((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

unsigned int	**make_rays_array(t_scn *nscn)
{
	unsigned int 	x;
	unsigned int	y;
	unsigned int	**arr;

	y = 0;
	if (!(arr = (unsigned int**)malloc(nscn->n_rsltn.y * sizeof(unsigned int*))))
		return (NULL);
	while (y < nscn->n_rsltn.y)
	{
		if (!(arr[y] = (unsigned int*)malloc(nscn->n_rsltn.x * sizeof(unsigned int))))
			return (NULL);
		y++;
	}
	y = 0;
	x = 0;
	while (y < nscn->n_rsltn.y)
	{
		while (x < nscn->n_rsltn.x)
		{
			arr[y][x] = (unsigned int)cnvrse2argb(0, 0, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
	return (arr);
}

unsigned int	**launch_rays(t_scn *nscn, unsigned int **rays_arr)
{
	int		x;
	int		y;
	t_ray	*tmp;

	x = 0;
	y = 0;
	tmp = trace_ray(nscn, x, y, 1);
	while (y < nscn->n_rsltn.y)
	{
		while (x < nscn->n_rsltn.x)
		{
			rays_arr[y][x] = (unsigned int)cnvrse2argb(tmp->a, tmp->r, tmp->g, tmp->b);
			x++;
		}
		x = 0;
		y++;
	}
}

void	rays_node(t_scn *nscn)
{
	unsigned int	**rays_arr;
	
	rays_arr = make_rays_array(nscn);
	rays_arr = launch_rays(nscn, rays_arr);
	img2win(nscn, rays_arr);
}