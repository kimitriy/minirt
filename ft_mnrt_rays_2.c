/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:23:50 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:24:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	launch_rays(t_scn *lscn, unsigned int **rays_arr, t_ray *ray)
{
	unsigned int	x;
	unsigned int	y;
	t_2d_point		xy;

	if (lscn->n_cntr.cam > 0)
	{
		x = -1;
		y = -1;
		while (++y < lscn->n_rsltn.y)
		{
			while (++x < lscn->n_rsltn.x)
			{
				p2d_make(&xy, x, y);
				cnvrse2crtsn(lscn, &xy);
				cnvrse2xyz(&ray->head_p, lscn, &xy);
				trace_ray(lscn, ray);
				rays_arr[y][x] = (unsigned int)cnvrse2trgb(&ray->p_trgb);
				ray_null(ray);
			}
			x = 0;
		}
	}
	else
		arr_ground_color(lscn, rays_arr);
}

void	rays_node(t_scn *lscn, t_scn *nscn)
{
	unsigned int	**rays_arr;
	t_ray			ray;

	if (nscn->n_cntr.cam > 0)
		rays_arr = make_rays_array(lscn);
	else
		rays_arr = make_rays_array(nscn);
	ray_null(&ray);
	launch_rays(lscn, rays_arr, &ray);
	if (lscn->save != '+')
		mlx_node(nscn, rays_arr);
	else
		bmp_node(nscn, rays_arr);
}
