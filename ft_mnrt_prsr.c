/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:21:29 by rburton           #+#    #+#             */
/*   Updated: 2021/01/18 19:18:08 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	prsr_assist(char *line, t_prsr *np, char *field, int n)
{
	char	f;

	f = '0';
	while (line[np->i])
	{
		if ((ft_isdigit(line[np->i]) == 1 || line[np->i] == '.' || line[np->i] == '-') && np->j < n)
		{
			field[np->j] = line[np->i];
			np->i++;
			np->j++;
			f = '1';
		}
		else if (ft_isdigit(line[np->i]) == 0 && line[np->i] != '.' && f == '0')
			np->i++;
		else if (ft_isdigit(line[np->i]) == 0 && line[np->i] != '.' && f == '1')
			break ;
	}
	np->j = 0;
}

void	write_rsltn(t_scn *nscn, t_prsr *np)
{
	nscn->n_rsltn.x = ft_atoi(np->rx);
	nscn->n_rsltn.y = ft_atoi(np->ry);
}

void	write_ambnt(t_scn *nscn, t_prsr *np)
{
	nscn->n_ambnt.lvl = ft_atof(np->lvl);
	nscn->n_ambnt.r = ft_atoi(np->r);
	nscn->n_ambnt.g = ft_atoi(np->g);
	nscn->n_ambnt.b = ft_atoi(np->b);
}

void	write_cam(t_scn *nscn, t_prsr *np)
{
	t_cam *tmp;

	tmp = NULL;
	make_t_cam(nscn);
	tmp = nscn->n_cam->content;
	tmp->p.x = ft_atof(np->x);
	tmp->p.y = ft_atof(np->y);
	tmp->p.z = ft_atof(np->z);
	tmp->nx = ft_atof(np->nx);
	tmp->ny = ft_atof(np->ny);
	tmp->nz = ft_atof(np->nz);
	tmp->fov = ft_atoi(np->fov);
	nscn->n_cntr.cam++;
}

void	write_lght(t_scn *nscn, t_prsr *np)
{
	t_lght *tmp;
	
	tmp = NULL;
	make_t_lght(nscn);
	tmp = nscn->n_lght->content;
	tmp->p.x = ft_atof(np->x);
	tmp->p.y = ft_atof(np->y);
	tmp->p.z = ft_atof(np->z);
	tmp->lvl = ft_atof(np->lvl);
	tmp->r = ft_atoi(np->r);
	tmp->g = ft_atoi(np->g);
	tmp->b = ft_atoi(np->b);
	nscn->n_cntr.lght++;
}

void	write_pln(t_scn *nscn, t_prsr *np)
{
	t_pln *tmp;

	tmp = NULL;
	make_t_pln(nscn);
	tmp = nscn->n_pln->content;
	tmp->p.x = ft_atof(np->x);
	tmp->p.y = ft_atof(np->y);
	tmp->p.z = ft_atof(np->z);
	tmp->nx = ft_atof(np->nx);
	tmp->ny = ft_atof(np->ny);
	tmp->nz = ft_atof(np->nz);
	tmp->r = ft_atoi(np->r);
	tmp->g = ft_atoi(np->g);
	tmp->b = ft_atoi(np->b);
	nscn->n_cntr.pln++;
}

void	write_sphr(t_scn *nscn, t_prsr *np)
{
	t_sphr *tmp;

	tmp = NULL;
	make_t_sphr(nscn);
	tmp = nscn->n_sphr->content;
	tmp->p.x = ft_atof(np->x);
	tmp->p.y = ft_atof(np->y);
	tmp->p.z = ft_atof(np->z);
	tmp->d = ft_atof(np->d);
	tmp->r = ft_atoi(np->r);
	tmp->g = ft_atoi(np->g);
	tmp->b = ft_atoi(np->b);
	nscn->n_cntr.sphr++;
}

void	write_cyl(t_scn *nscn, t_prsr *np)
{
	t_cyl *tmp;

	tmp = NULL;
	make_t_cyl(nscn);
	tmp = nscn->n_cyl->content;
	tmp->p.x = ft_atof(np->x);
	tmp->p.y = ft_atof(np->y);
	tmp->p.z = ft_atof(np->z);
	tmp->nx = ft_atof(np->nx);
	tmp->ny = ft_atof(np->ny);
	tmp->nz = ft_atof(np->nz);
	tmp->d = ft_atof(np->d);
	tmp->h = ft_atof(np->h);
	tmp->r = ft_atoi(np->r);
	tmp->g = ft_atoi(np->g);
	tmp->b = ft_atoi(np->b);
	nscn->n_cntr.cyl++;
}

void	write_sqr(t_scn *nscn, t_prsr *np)
{
	t_sqr *tmp;

	tmp = NULL;
	make_t_sqr(nscn);
	tmp = nscn->n_sqr->content;
	tmp->p.x = ft_atof(np->x);
	tmp->p.y = ft_atof(np->y);
	tmp->p.z = ft_atof(np->z);
	tmp->nx = ft_atof(np->nx);
	tmp->ny = ft_atof(np->ny);
	tmp->nz = ft_atof(np->nz);
	tmp->side = ft_atof(np->side);
	tmp->r = ft_atoi(np->r);
	tmp->g = ft_atoi(np->g);
	tmp->b = ft_atoi(np->b);
	nscn->n_cntr.sqr++;
}

void	write_trngl(t_scn *nscn, t_prsr *np)
{
	t_trngl *tmp;

	tmp = NULL;
	make_t_trngl(nscn);
	tmp = nscn->n_trngl->content;

	tmp->p1.x = ft_atof(np->x);
	tmp->p1.y = ft_atof(np->y);
	tmp->p1.z = ft_atof(np->z);
	tmp->p2.x = ft_atof(np->x2);
	tmp->p2.y = ft_atof(np->y2);
	tmp->p2.z = ft_atof(np->z2);
	tmp->p3.x = ft_atof(np->x3);
	tmp->p3.y = ft_atof(np->y3);
	tmp->p3.z = ft_atof(np->z3);
	tmp->r = ft_atoi(np->r);
	tmp->g = ft_atoi(np->g);
	tmp->b = ft_atoi(np->b);

	nscn->n_cntr.trngl++;
}

void	prsr_rsltn(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 2)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->rx, 5);
		else if (np->n == 1)
			prsr_assist(line, np, np->ry, 5);
		np->n++;
	}
	write_rsltn(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_ambnt(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 4)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->lvl, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 2)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 3)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_ambnt(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_cam(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 7)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->nx, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->ny, 42);
		else if (np->n == 5)
			prsr_assist(line, np, np->nz, 42);
		else if (np->n == 6)
			prsr_assist(line, np, np->fov, 5);
		np->n++;
	}
	write_cam(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_lght(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 7)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->lvl, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 5)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 6)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_lght(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_sphr(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 7)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->d, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 5)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 6)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_sphr(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_pln(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 9)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->nx, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->ny, 42);
		else if (np->n == 5)
			prsr_assist(line, np, np->nz, 42);
		else if (np->n == 6)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 7)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 8)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_pln(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_sqr(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 10)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->nx, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->ny, 42);
		else if (np->n == 5)
			prsr_assist(line, np, np->nz, 42);
		else if (np->n == 6)
			prsr_assist(line, np, np->side, 42);
		else if (np->n == 7)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 8)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 9)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_sqr(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_cyl(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 11)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->nx, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->ny, 42);
		else if (np->n == 5)
			prsr_assist(line, np, np->nz, 42);
		else if (np->n == 6)
			prsr_assist(line, np, np->d, 42);
		else if (np->n == 7)
			prsr_assist(line, np, np->h, 42);
		else if (np->n == 8)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 9)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 10)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_cyl(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_trngl(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 12)
	{
		if (np->n == 0)
			prsr_assist(line, np, np->x, 42);
		else if (np->n == 1)
			prsr_assist(line, np, np->y, 42);
		else if (np->n == 2)
			prsr_assist(line, np, np->z, 42);
		else if (np->n == 3)
			prsr_assist(line, np, np->x2, 42);
		else if (np->n == 4)
			prsr_assist(line, np, np->y2, 42);
		else if (np->n == 5)
			prsr_assist(line, np, np->z2, 42);
		else if (np->n == 6)
			prsr_assist(line, np, np->x3, 42);
		else if (np->n == 7)
			prsr_assist(line, np, np->y3, 42);
		else if (np->n == 8)
			prsr_assist(line, np, np->z3, 42);
		else if (np->n == 9)
			prsr_assist(line, np, np->r, 5);
		else if (np->n == 10)
			prsr_assist(line, np, np->g, 5);
		else if (np->n == 11)
			prsr_assist(line, np, np->b, 5);
		np->n++;
	}
	write_trngl(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void   prsr(char **scn_arr, int size, t_scn *nscn, t_prsr *np)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (scn_arr[i][0] == 'R' && ft_isalpha(scn_arr[i][1]) == 0)
			prsr_rsltn(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 'A' && ft_isalpha(scn_arr[i][1]) == 0)
			prsr_ambnt(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 'c' && ft_isalpha(scn_arr[i][1]) == 0)
			prsr_cam(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 'l' && ft_isalpha(scn_arr[i][1]) == 0)
			prsr_lght(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 's' && scn_arr[i][1] == 'p')
			prsr_sphr(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 'p' && scn_arr[i][1] == 'l')
			prsr_pln(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 's' && scn_arr[i][1] == 'q')
			prsr_sqr(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 'c' && scn_arr[i][1] == 'y')
			prsr_cyl(scn_arr[i], nscn, np);
		if (scn_arr[i][0] == 't' && scn_arr[i][1] == 'r')
			prsr_trngl(scn_arr[i], nscn, np);
		i++;
	}
}