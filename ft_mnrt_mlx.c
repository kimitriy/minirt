/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 23:13:59 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 19:38:18 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/*
void	create_window(void)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "Hello, world!");

	mlx_loop(mlx);
}

void	create_image(void)
{
	t_data	img;
	void	*mlx;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pix, &img.line_lngth, &img.endian);
}
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lngth + x * (data->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}

void	make_new_sqr(t_draw_sqr *new_sqr)
{
	new_sqr->start_x = 100;
	new_sqr->start_y = 100;
	new_sqr->side = 300;
	new_sqr->color = 0x00FF0000;
}

void	draw_sqr(t_data *data, t_draw_sqr *sqr)
{
	int		x;
	int		y;

	x = sqr->start_x;
	y = sqr->start_y;
	while (y < (sqr->start_y + sqr->side))
	{
		while (x < (sqr->start_x + sqr->side))
		{
			my_mlx_pixel_put(data, x, y, sqr->color);
			x++;
		}
		x = sqr->start_x;
		y++;
	}
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

void	make_new_crcl(t_draw_crcl *new_crcl)
{
	new_crcl->start_x = 500;
	new_crcl->start_y = 500;
	new_crcl->r = 100;
	new_crcl->color = 0x0000FF00;
	new_crcl->root1 = '\0';
	new_crcl->root2 = '\0';
}

void	crcl_eqsn(t_data *data, t_draw_crcl *crcl, int x)
{
	int		dscrmnnt;

	dscrmnnt = 4 * powf(crcl->start_y, 2) - 4 * powf(x, 2) + 8 * crcl->start_x * x - 4 * powf(crcl->start_x, 2) - 4 * powf(crcl->start_y, 2) + 4 * powf(crcl->r, 2);
	if (dscrmnnt == 0)
	{
		crcl->root1 = (int)(2 * crcl->start_y + sqrtf(dscrmnnt)) / 2;
		my_mlx_pixel_put(data, x, crcl->root1, crcl->color);
	}
	else if (dscrmnnt > 0)
	{
		crcl->root1 = (int)(2 * crcl->start_y + sqrtf(dscrmnnt)) / 2;
		my_mlx_pixel_put(data, x, crcl->root1, crcl->color);
		crcl->root2 = (int)(2 * crcl->start_y - sqrtf(dscrmnnt)) / 2;
		my_mlx_pixel_put(data, x, crcl->root2, crcl->color);
	}
}

void	draw_crcl(t_data *data, t_draw_crcl *crcl)
{
	int		x;
	int		y;

	x = crcl->start_x - crcl->r;
	y = crcl->start_y - crcl->r;
	while (y < (crcl->start_y + crcl->r))
	{
		while (x < (crcl->start_x + crcl->r))
		{
			crcl_eqsn(data, crcl, x);
			x++;
		}
		x = crcl->start_x - crcl->start_x;
		y++;
	}
}

void	img2win(t_scn *nscn, unsigned int **arr)
{
	void		*mlx; //pointer for mlx instance
	void		*mlx_win; //pointer for mlx window instance
	t_data		img;
	// t_draw_sqr	new_sqr;
	// t_draw_crcl	new_crcl;

	
	// make_new_sqr(&new_sqr);
	// make_new_crcl(&new_crcl);
	
	mlx = mlx_init(); //initialises mlx instance
	mlx_win = mlx_new_window(mlx, nscn->n_rsltn.x, nscn->n_rsltn.y, "Hello, world!"); //initialises new window
	img.img = mlx_new_image(mlx, nscn->n_rsltn.x, nscn->n_rsltn.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pix, &img.line_lngth, &img.endian);
	//draw_sqr(&img, &new_sqr);
	//draw_crcl(&img, &new_crcl);
	draw_from_arr(nscn, &img, arr);
	//my_mlx_pixel_put(&img, 500, 100, 0x00FF0000); //x, y
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx); //holds the window opened
}

// void	mlx_node(void)
// {
// 	img2win();
// }