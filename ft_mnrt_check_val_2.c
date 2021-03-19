/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check_val_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:08:58 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 09:10:41 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_val_rsltn(t_prsr *np)
{
	check_val_uint(np->rx, 16000, "Unable to apply resolution.");
	check_val_uint(np->ry, 16000, "Unable to apply resolution.");
}

void	check_val_ambnt(t_prsr *np)
{
	check_val_color(np);
}

void	check_val_cam(t_prsr *np)
{
	check_val_uint(np->fov, 180, "Unable to apply FOV.");
	check_val_coordinates(np->x, np->y, np->z);
}

void	check_val_lght(t_prsr *np)
{
	check_val_coordinates(np->x, np->y, np->z);
	check_val_color(np);
}

void	check_val_pln(t_prsr *np)
{
	check_val_coordinates(np->x, np->y, np->z);
	check_val_coordinates(np->nx, np->ny, np->nz);
	check_val_color(np);
}
