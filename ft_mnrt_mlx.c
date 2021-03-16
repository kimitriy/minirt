/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 23:13:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/16 15:52:53 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lngth + x * (data->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}

void	draw_from_arr(t_scn * nscn, t_data *data, unsigned int **arr)
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

// void	ft_putnbr(int n)
// {
// 	char	ch;
	
// 	if (n == -2147483648)
// 		write(1, "-2147483648", 11);
// 	else if (n < 0)
// 	{
// 		write(1, "-", 1);
// 		ft_putnbr(n * (-1));
// 	}
// 	else if (n > 9)
// 	{
// 		ft_putnbr(n / 10);
// 		ft_putnbr(n % 10);
// 	}
// 	else
// 	{	
// 		ch = n + '0';
// 		write(1, &ch, 1);
// 	}
// }

int		key_hook(int keycode, t_scn *nscn)
{
	ft_putnbr(1, keycode, 10, "0123456789");
	write(1, "\n", 1);
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
		lookat_node(nscn);
	}
	return (0);
}

int		close_mlx_win(int keycode, t_vars *vrs)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vrs->mlx, vrs->win);
		exit (0);
	}
	return (0);
}

int		stop_ex(t_vars *vrs)
{
	mlx_destroy_window(vrs->mlx, vrs->win);
	exit (0);
	return (0);
}

void	img2win(t_scn *nscn, unsigned int **arr)
{
	if (arr != NULL)
		draw_from_arr(nscn, &nscn->dt, arr);
	mlx_put_image_to_window(nscn->vrs.mlx, nscn->vrs.win, nscn->dt.img, 0, 0);
	mlx_destroy_image(nscn->vrs.mlx, nscn->dt.img);
	nscn->dt.img = mlx_new_image(nscn->vrs.mlx, nscn->n_rsltn.x, nscn->n_rsltn.y);
	nscn->dt.addr = mlx_get_data_addr(nscn->dt.img, &nscn->dt.bits_per_pix, &nscn->dt.line_lngth, &nscn->dt.endian);

	// mlx_loop(nscn->vrs.mlx); //holds the window opened
}

// void	img2win(t_scn *nscn, unsigned int **arr)
// {
// 	void		*mlx; //pointer for mlx instance
// 	void		*mlx_win; //pointer for mlx window instance
// 	t_data		img;
	
// 	mlx = mlx_init(); //initialises mlx instance
// 	mlx_win = mlx_new_window(mlx, nscn->n_rsltn.x, nscn->n_rsltn.y, "Hello, world!"); //initialises new window
// 	img.img = mlx_new_image(mlx, nscn->n_rsltn.x, nscn->n_rsltn.y);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pix, &img.line_lngth, &img.endian);
	
// 	draw_from_arr(nscn, &img, arr);
	
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

// 	mlx_loop(mlx); //holds the window opened
// }

void	mlx_node(t_scn *nscn, unsigned int **arr)
{
	nscn->vrs.mlx = mlx_init(); //initialises mlx instance
	nscn->vrs.win = mlx_new_window(nscn->vrs.mlx, nscn->n_rsltn.x, nscn->n_rsltn.y, "miniRT"); //initialises new window
	
	nscn->dt.img = mlx_new_image(nscn->vrs.mlx, nscn->n_rsltn.x, nscn->n_rsltn.y);
	nscn->dt.addr = mlx_get_data_addr(nscn->dt.img, &nscn->dt.bits_per_pix, &nscn->dt.line_lngth, &nscn->dt.endian);
	
	mlx_key_hook(nscn->vrs.win, key_hook, nscn);
	mlx_hook(nscn->vrs.win, 2, 1L<<0, close_mlx_win, &nscn->vrs);
	mlx_hook(nscn->vrs.win, 17, 1L << 2, stop_ex, &nscn->vrs);

	img2win(nscn, arr);

	mlx_loop(nscn->vrs.mlx); //holds the window opened
}