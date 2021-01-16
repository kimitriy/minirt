/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:35:03 by rburton           #+#    #+#             */
/*   Updated: 2021/01/16 18:03:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	ray_eqtn(t_ray *ray, int dstnce, int gen)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		ray->hit_point[i].x = 0;
		ray->hit_point[i].y = 0;
		ray->hit_point[i].z = 0;
		i++;
	}
	ray->vctr = v_make(ray->tail_point, ray->head_point);
	ray->dstnce = dstnce;
	nv_n_prdct(ray->vctr, ray->dstnce);
	ray->hit_point[gen] = *p_make(ray->vctr->x + ray->tail_point->x, ray->vctr->y + ray->tail_point->y, ray->vctr->z + ray->tail_point->z);
}

void	trace_ray()
{

}

void   func_throwing_3G_of_rays(t_scn *nscn, int x, int y, int z)
{
    t_ray   *nray;

    if (!(nray = (t_ray*)malloc(1 * sizeof(t_ray))))
		nray = NULL;
    nray->cnvs_xy.rsltn.x = nscn->n_rsltn.x;
    nray->cnvs_xy.rsltn.y = nscn->n_rsltn.y;
    nray->cnvs_xy.x_crtsn = 960;
    nray->cnvs_xy.y_crtsn = -540;
	cnvrse2ncrtsn(&nray->cnvs_xy);
    nray->tail_point = p_make(x, y, z);
    nray->head_point = cnvrse2xyz(nscn, &nray->cnvs_xy);
	ray_eqtn(nray, 100, 0);
	printf("ray(tail(%f, %f, %f), head(%f, %f, %f), vctr(%f, %f, %f), length:%f, nrmlsd(%f, %f, %f), dstnc:%f, h_point(%f, %f, %f))\n", nray->tail_point->x, nray->tail_point->y, nray->tail_point->z, nray->head_point->x, nray->head_point->y, nray->head_point->z, nray->vctr->x, nray->vctr->y, nray->vctr->z, nray->vctr->lngth, nray->vctr->nx, nray->vctr->ny, nray->vctr->nz, nray->dstnce, nray->hit_point[0].x, nray->hit_point[0].y, nray->hit_point[0].z);
    //return (new_ray);
}

void	rays_array(t_scn *nscn)
{
	int 	x;
	int		y;
	

	x = 0;
	y = 0;

}

void	rays_node(t_scn *nscn)
{
	//printf("%d", nscn->n_rsltn.x);
	trace_ray(nscn, 0, 0, 0);
}