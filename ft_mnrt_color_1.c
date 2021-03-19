/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_color_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:36:19 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 09:41:44 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	color_make(t_color *color, unsigned int r,
	unsigned int g, unsigned int b)
{
	color->t = 0;
	color->r = r;
	color->g = g;
	color->b = b;
}

void	color_null(t_color *color)
{
	color->t = 0;
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	color_copy(t_color *to, t_color *from)
{
	to->t = from->t;
	to->r = from->r;
	to->g = from->g;
	to->b = from->b;
}

void	to_cmyk(t_cmyk *out, t_color *trgb)
{
	float r_;
	float g_;
	float b_;

	r_ = (float)trgb->r / 255;
	g_ = (float)trgb->g / 255;
	b_ = (float)trgb->b / 255;
	out->k = 1 - max_3floats(r_, g_, b_);
	out->c = (1 - r_ - out->k) / (1 - out->k);
	out->m = (1 - g_ - out->k) / (1 - out->k);
	out->y = (1 - b_ - out->k) / (1 - out->k);
}

void	to_rgb(t_color *out, t_cmyk *cmyk)
{
	out->r = (unsigned int)roundf(255 * (1 - cmyk->c) * (1 - cmyk->k));
	out->g = (unsigned int)roundf(255 * (1 - cmyk->m) * (1 - cmyk->k));
	out->b = (unsigned int)roundf(255 * (1 - cmyk->y) * (1 - cmyk->k));
}
