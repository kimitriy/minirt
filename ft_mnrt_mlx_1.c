/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_mlx_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 23:13:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/20 01:14:06 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lngth + x * (data->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}

void	draw_from_arr(t_scn *nscn, t_data *data, unsigned int **arr)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 0;
	while (y < nscn->n_rsltn.y)
	{
		while (x < nscn->n_rsltn.x)
		{
			my_mlx_pixel_put(data, x, y, (unsigned int)arr[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}

int		key_hook(int keycode, t_scn *nscn)
{
	if (keycode == 13)
	{
		if (nscn->n_cam->next != NULL)
			nscn->n_cam = nscn->n_cam->next;
		else
			nscn->n_cam = nscn->frst_cam;
		nscn->n_lght = nscn->frst_lght;
		nscn->n_sphr = nscn->frst_sphr;
		nscn->n_pln = nscn->frst_pln;
		nscn->n_sqr = nscn->frst_sqr;
		nscn->n_trngl = nscn->frst_trngl;
		nscn->n_cyl = nscn->frst_cyl;
		mlx_destroy_window(nscn->vrs.mlx, nscn->vrs.win);
		lookat_node(nscn, 77777);
	}
	return (0);
}

int		close_mlx_win(int keycode, t_vars *vrs)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vrs->mlx, vrs->win);
		exit(0);
	}
	return (0);
}
