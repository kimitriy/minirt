/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr2d_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 21:35:34 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:04:51 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	v_xy(t_vxy *out, t_2d_point *tail, t_2d_point *head)
{
	out->x = head->x - tail->x;
	out->y = head->y - tail->y;
}

void	v2d_null(t_vctr2d *vctr)
{
	vctr->xy.x = 0;
	vctr->xy.y = 0;
	vctr->lngth = 0;
}

void	v2d_lngth(t_vctr2d *vctr)
{
	vctr->lngth = sqrtf(powf(vctr->xy.x, 2) + powf(vctr->xy.y, 2));
}
