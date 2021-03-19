/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_bmp_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:16 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:41:27 by rburton          ###   ########.fr       */
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

void			make_bmp_hdr(t_scn *nscn, int file_size, int fd)
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
	hdr[14 + 14] = (unsigned char)(24);
	write(fd, hdr, 54);
}

void			pxl_put(unsigned int **arr, unsigned int h,
	unsigned int w, int fd)
{
	unsigned char	c;

	c = (unsigned char)(arr[h][w] >> 0 & 0xFF);
	write(fd, &c, 1);
	c = (unsigned char)(arr[h][w] >> 8 & 0xFF);
	write(fd, &c, 1);
	c = (unsigned char)(arr[h][w] >> 16 & 0xFF);
	write(fd, &c, 1);
}
