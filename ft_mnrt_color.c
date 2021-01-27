/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:36:19 by rburton           #+#    #+#             */
/*   Updated: 2021/01/27 16:51:28 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	color_make(t_color *color, unsigned int r, unsigned int g, unsigned int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}

void	color_copy(t_color *to, t_color *from)
{
	to->t = from->t;
    to->r = from->r;
	to->g = from->g;
	to->b = from->b;
}

void	color_modify(t_color *color, t_lum *lum)
{
	int		f;

	f = 200;
    color->t = 0;
    if (lum->l >= 0.75)
    {
        if (color->r < f * lum->l)
            color->r = f * lum->l;
        if (color->g < f * lum->l)
            color->g = f * lum->l;
        if (color->b < f * lum->l)
            color->b = f * lum->l;
    }
    else
    {
        color->r = color->r * lum->l;
        color->g = color->g * lum->l;
        color->b = color->b * lum->l;
    }
}