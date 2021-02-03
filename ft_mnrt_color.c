/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:36:19 by rburton           #+#    #+#             */
/*   Updated: 2021/02/03 15:27:27 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	color_make(t_color *color, unsigned int r, unsigned int g, unsigned int b)
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

// void	color_modify(t_color *out, t_color *in, t_lum *lum)
// {
// 	int		f;

// 	f = 55;
//     if (lum->l >= 0.95)
//     {
//         if (color->r < f * lum->l)
//             color->r = f * lum->l;
//         if (color->g < f * lum->l)
//             color->g = f * lum->l;
//         if (color->b < f * lum->l)
//             color->b = f * lum->l;
//     }
//     else
//     {
//         color->r = color->r * lum->l;
//         color->g = color->g * lum->l;
//         color->b = color->b * lum->l;
//     }
// }

void	to_cmyk(t_cmyk *out, t_color *trgb)
{
	float r_;
	float g_;
	float b_;

	r_ = trgb->r / 255;
	g_ = trgb->g / 255;
	b_ = trgb->b / 255;
	out->k = (int)(1 - max_3uints(r_, g_, b_)) * 100;
	out->c = (int)((1 - r_ - out->k) / (1 - out->k)) * 100;
	out->m = (int)((1 - g_ - out->k) / (1 - out->k)) * 100;
	out->y = (int)((1 - b_ - out->k) / (1 - out->k)) * 100;
}

void	to_rgb(t_color *out, t_cmyk *cmyk)
{
	out->r = 255 * (1 - cmyk->c / 100) * (1 - cmyk->k / 100);
	out->g = 255 * (1 - cmyk->m / 100) * (1 - cmyk->k / 100);
	out->b = 255 * (1 - cmyk->y / 100) * (1 - cmyk->k / 100);
}

void	sum_color(t_color *out, t_color *surface, t_color *light)
{
	t_cmyk	srfc;
	t_cmyk	lght;
	t_cmyk	sum;

	to_cmyk(&srfc, surface);
	to_cmyk(&lght, light);
	to_cmyk(&sum, out);
	
	sum.c = min_2uints(100, (srfc.c + lght.c));
	sum.m = min_2uints(100, (srfc.m + lght.m));
	sum.y = min_2uints(100, (srfc.y + lght.y));
	sum.k = min_2uints(100, (srfc.k + lght.k));

	to_rgb(out, &sum);
}

void	lvl_apply(t_color *out, t_color *in, t_lum *lum)
{
	// int		f;

	// f = 55;
	// if (lum->l >= 0.95)
	// {
	// 	out->r += in->r * lum->l;
	// 	out->g += in->g * lum->l;
	// 	out->b += in->b * lum->l;
	// }
	// else
	// {
	out->r = out->r + in->r * lum->l > 255 ? 255 : out->r + in->r * lum->l;
	out->g = out->g + in->g * lum->l > 255 ? 255 : out->g + in->g * lum->l;
	out->b = out->b + in->b * lum->l > 255 ? 255 : out->b + in->b * lum->l;
	// }
}

void    color_node(t_ray *ray, t_lum *lum)
{
    sum_color(&ray->sum_trgb, &ray->obj_trgb, &lum->l_trgb);
	lvl_apply(&ray->p_trgb, &ray->sum_trgb, lum);
}