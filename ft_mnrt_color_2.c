/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_color_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:41:04 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 09:41:32 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	sum_color(t_color *out, t_color *surface, t_color *light)
{
	t_cmyk	srfc;
	t_cmyk	lght;
	t_cmyk	sum;
	float	tmp_min;

	to_cmyk(&srfc, surface);
	to_cmyk(&lght, light);
	to_cmyk(&sum, out);
	tmp_min = min_2floats(100, (srfc.c + lght.c));
	sum.c = tmp_min > 1 ? 1 : tmp_min;
	tmp_min = min_2floats(100, (srfc.m + lght.m));
	sum.m = tmp_min > 1 ? 1 : tmp_min;
	tmp_min = min_2floats(100, (srfc.y + lght.y));
	sum.y = tmp_min > 1 ? 1 : tmp_min;
	tmp_min = min_2floats(100, (srfc.k + lght.k));
	sum.k = tmp_min > 1 ? 1 : tmp_min;
	to_rgb(out, &sum);
}

void	lvl_apply(t_color *out, t_color *in, t_lum *lum)
{
	out->r = out->r + in->r * lum->l > 255 ? 255 : out->r + in->r * lum->l;
	out->g = out->g + in->g * lum->l > 255 ? 255 : out->g + in->g * lum->l;
	out->b = out->b + in->b * lum->l > 255 ? 255 : out->b + in->b * lum->l;
}

void	color_node(t_scn *lscn, t_ray *ray, t_lum *lum)
{
	if (lscn->n_cntr.lght > 0)
		sum_color(&ray->sum_trgb, &ray->obj_trgb, &lum->l_trgb);
	else
		sum_color(&ray->sum_trgb, &ray->obj_trgb, &lscn->n_ambnt.trgb);
	lvl_apply(&ray->p_trgb, &ray->sum_trgb, lum);
}
