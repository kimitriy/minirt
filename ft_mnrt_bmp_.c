/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:16 by rburton           #+#    #+#             */
/*   Updated: 2021/03/16 02:29:02 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

unsigned int	get_pddng(t_scn *nscn)
{
	int		rmndr;

	rmndr = nscn->n_rsltn.x * 3 % 4;
    if (rmndr != 0)
		return (4 - rmndr);
	else
		return (0);
}

unsigned char	*make_bmp_hdr(t_scn *nscn, int file_size)
{
    static unsigned char	hdr[54];
    
    hdr[0] = (unsigned char)('B');
    hdr[1] = (unsigned char)('M');
    hdr[2] = (unsigned char)(file_size);
    hdr[3] = (unsigned char)(file_size >> 8);
    hdr[4] = (unsigned char)(file_size >> 16);
    hdr[5] = (unsigned char)(file_size >> 24);
    hdr[10] = (unsigned char)(14 + 40);
    hdr[14 + 0] = (unsigned char)(40);
    hdr[14 + 4] = (unsigned char)(nscn->n_rsltn.x);
    hdr[14 + 5] = (unsigned char)(nscn->n_rsltn.x >> 8);
    hdr[14 + 6] = (unsigned char)(nscn->n_rsltn.x >> 16);
    hdr[14 + 7] = (unsigned char)(nscn->n_rsltn.x >> 24);
    hdr[14 + 8] = (unsigned char)(nscn->n_rsltn.y);
    hdr[14 + 9] = (unsigned char)(nscn->n_rsltn.y >> 8);
    hdr[14 + 10] = (unsigned char)(nscn->n_rsltn.y >> 16);
    hdr[14 + 11] = (unsigned char)(nscn->n_rsltn.y >> 24);
    hdr[14 + 12] = (unsigned char)(1);
    hdr[14 + 14] = (unsigned char)(3 * 8);
    return (hdr);
    // write(fd, "\n", 1);
}

void	img2pic(t_scn *nscn, unsigned char *image, int fd, int padding_size)
{
    // (void)arr;
    // (void)padding_size;
    // (void)nscn;
    int		h;
    // unsigned int     w;
    // unsigned int     p;
    const unsigned char padding[3] = {0, 0, 0};

    // p = 0;
    h = nscn->n_rsltn.y + 1;
    while (--h >= 0)
    {
        write(fd, image + (h * nscn->n_rsltn.x * 3), 3 * nscn->n_rsltn.x);
        write(fd, padding, padding_size);
    }
}

void    bmp_node(t_scn *nscn, unsigned int **arr)
{
    // nscn->vrs.mlx = mlx_init(); //initialises mlx instance
	// nscn->vrs.win = mlx_new_window(nscn->vrs.mlx, nscn->n_rsltn.x, nscn->n_rsltn.y, "miniRT"); //initialises new window
    // nscn->dt.img = mlx_new_image(nscn->vrs.mlx, nscn->n_rsltn.x, nscn->n_rsltn.y);
	// nscn->dt.addr = mlx_get_data_addr(nscn->dt.img, &nscn->dt.bits_per_pix, &nscn->dt.line_lngth, &nscn->dt.endian);
    int     fd;
	unsigned int	pddng;
    unsigned int	file_size;
    int                 padding_size;
    unsigned char   image[nscn->n_rsltn.y][nscn->n_rsltn.x][3];
    int             i;
    int             j;

    i = -1;
    //return (((trgb->t & 0xff) << 24) + ((trgb->r & 0xff) << 16) +
    //((trgb->g & 0xff) << 8) + (trgb->b & 0xff));
    while (++i < (int)nscn->n_rsltn.y)
    {
        j = nscn->n_rsltn.x;
        while (--j >= 0)
        {
            image[i][j][2] = arr[i][j] >> 16 & 0xFF;
            image[i][j][1] = arr[i][j] >> 8 & 0xFF;
            image[i][j][0] = arr[i][j] & 0xFF;
        }
    }
    if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == 0)
        err_message("Unable to create screenshot.");

    pddng = get_pddng(nscn);
    padding_size = (4 - (nscn->n_rsltn.x * 3) % 4) % 4;
    file_size = (nscn->n_rsltn.x * 3 + padding_size) * nscn->n_rsltn.y + 54;
	
	write(fd, make_bmp_hdr(nscn, file_size), 54);
    img2pic(nscn, (unsigned char*)image, fd, padding_size);
	close(fd);
	write(1, "Screenshot successfully created.\n", 33);
    exit(0);
}