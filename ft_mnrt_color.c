/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:36:19 by rburton           #+#    #+#             */
/*   Updated: 2021/02/02 11:19:18 by rburton          ###   ########.fr       */
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

void	color_calc(t_color *out, t_color *in, t_lum *lum)
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
    //color_null(&ray->p_trgb);
	color_calc(&ray->p_trgb, &ray->obj_trgb, lum);
}