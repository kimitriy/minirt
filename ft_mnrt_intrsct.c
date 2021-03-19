/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_intrsct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:45:03 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 12:41:47 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_objcts(t_scn *lscn, t_ray *ray)
{
	check_sphrs(lscn, ray);
	check_trngls(lscn, ray);
	check_sqrs(lscn, ray);
	check_cyls(lscn, ray);
	check_plns(lscn, ray);
}

void	check_lghts(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_lght	*lght;

	lscn->n_lght = lscn->frst_lght;
	i = 0;
	color_null(&ray->p_trgb);
	while (i < lscn->n_cntr.lght)
	{
		lght = lscn->n_lght->content;
		if (ray->dist < INFINITY)
		{
			ray->tail_p = ray->hit_p;
			ray->head_p = lght->p;
			ray->sgm = 1;
			v_make(&ray->vctr[1], &ray->tail_p, &ray->head_p);
			check_objcts(lscn, ray);
		}
		if (ray->dist < INFINITY && ray->sgm > 0)
			lum_node(lscn, lght, ray);
		if (lscn->n_lght->next != NULL)
			lscn->n_lght = lscn->n_lght->next;
		ray->shdw = '\0';
		i++;
	}
}

void	intrsct_node(t_scn *lscn, t_ray *ray)
{
	t_lght	nolght;

	check_objcts(lscn, ray);
	if (ray->dist < INFINITY && lscn->n_cntr.lght > 0)
		check_lghts(lscn, ray);
	else if (ray->dist < INFINITY && lscn->n_cntr.lght == 0)
	{
		t_lght_null(&nolght);
		lum_node(lscn, &nolght, ray);
	}
}
