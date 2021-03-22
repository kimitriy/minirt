/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:06:00 by rburton           #+#    #+#             */
/*   Updated: 2021/03/22 13:36:01 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

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
