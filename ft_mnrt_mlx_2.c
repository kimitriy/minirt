/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_mlx_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:28:10 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 13:28:32 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int		stop_ex(t_vars *vrs)
{
	mlx_destroy_window(vrs->mlx, vrs->win);
	exit(0);
	return (0);
}

void	img2win(t_scn *nscn, unsigned int **arr)
{
	if (arr != NULL)
		draw_from_arr(nscn, &nscn->dt, arr);
	mlx_put_image_to_window(nscn->vrs.mlx, nscn->vrs.win, nscn->dt.img, 0, 0);
	mlx_destroy_image(nscn->vrs.mlx, nscn->dt.img);
	nscn->dt.img = mlx_new_image(nscn->vrs.mlx,
		nscn->n_rsltn.x, nscn->n_rsltn.y);
	nscn->dt.addr = mlx_get_data_addr(nscn->dt.img, &nscn->dt.bits_per_pix,
		&nscn->dt.line_lngth, &nscn->dt.endian);
}

void	mlx_node(t_scn *nscn, unsigned int **arr)
{
	nscn->vrs.mlx = mlx_init();
	nscn->vrs.win = mlx_new_window(nscn->vrs.mlx,
		nscn->n_rsltn.x, nscn->n_rsltn.y, "miniRT");
	nscn->dt.img = mlx_new_image(nscn->vrs.mlx,
		nscn->n_rsltn.x, nscn->n_rsltn.y);
	nscn->dt.addr = mlx_get_data_addr(nscn->dt.img, &nscn->dt.bits_per_pix,
		&nscn->dt.line_lngth, &nscn->dt.endian);
	mlx_key_hook(nscn->vrs.win, key_hook, nscn);
	mlx_hook(nscn->vrs.win, 2, 1L << 0, close_mlx_win, &nscn->vrs);
	mlx_hook(nscn->vrs.win, 17, 1L << 2, stop_ex, &nscn->vrs);
	img2win(nscn, arr);
	mlx_loop(nscn->vrs.mlx);
}
