/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check_val_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:09:01 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 09:11:08 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_val_sphr(t_prsr *np)
{
	check_val_coordinates(np->x, np->y, np->z);
	check_val_float(np->d, "Unable to apply diameter.");
	check_val_color(np);
}

void	check_val_cyl(t_prsr *np)
{
	check_val_coordinates(np->x, np->y, np->z);
	check_val_coordinates(np->nx, np->ny, np->nz);
	check_val_float(np->d, "Unable to apply diameter.");
	check_val_float(np->d, "Unable to apply height.");
	check_val_color(np);
}

void	check_val_sqr(t_prsr *np)
{
	check_val_coordinates(np->x, np->y, np->z);
	check_val_coordinates(np->nx, np->ny, np->nz);
	check_val_float(np->side, "Unable to apply side.");
	check_val_color(np);
}

void	check_val_trngl(t_prsr *np)
{
	check_val_coordinates(np->x, np->y, np->z);
	check_val_coordinates(np->x2, np->y2, np->z2);
	check_val_coordinates(np->x3, np->y3, np->z3);
	check_val_color(np);
}

void	check_values_node(t_prsr *np, char obj)
{
	if (obj == 'r')
		check_val_rsltn(np);
	else if (obj == 'a')
		check_val_ambnt(np);
	else if (obj == 'o')
		check_val_cam(np);
	else if (obj == 'l')
		check_val_lght(np);
	else if (obj == 'p')
		check_val_pln(np);
	else if (obj == 's')
		check_val_sphr(np);
	else if (obj == 'c')
		check_val_cyl(np);
	else if (obj == 'q')
		check_val_sqr(np);
	else if (obj == 't')
		check_val_trngl(np);
}
