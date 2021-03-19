/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_bmp_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:26:54 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 19:36:40 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	pddng_put(int fd)
{
	unsigned char	c;

	c = (unsigned char)(0);
	write(fd, &c, 1);
}

void	img2pic(t_scn *nscn, unsigned int **arr, unsigned int pddng, int fd)
{
	int				h;
	unsigned int	w;
	unsigned int	p;

	p = 0;
	w = 0;
	h = nscn->n_rsltn.y - 1;
	while (h >= 0)
	{
		while (w < nscn->n_rsltn.x)
		{
			pxl_put(arr, h, w, fd);
			w++;
		}
		while (p < pddng)
		{
			pddng_put(fd);
			p++;
		}
		w = 0;
		p = 0;
		h--;
	}
}

void	bmp_node(t_scn *nscn, unsigned int **arr)
{
	int				fd;
	unsigned int	pddng;
	unsigned int	file_size;

	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == 0)
		err_message("Unable to create screenshot.");
	pddng = get_pddng(nscn);
	file_size = (nscn->n_rsltn.x * 3 + pddng) * nscn->n_rsltn.y + 54;
	make_bmp_hdr(nscn, file_size, fd);
	img2pic(nscn, arr, pddng, fd);
	close(fd);
	write(1, "Screenshot successfully created.\n", 33);
	exit(0);
}
