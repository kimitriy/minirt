/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:06:05 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:08:54 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

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

void	prsr_sqr_if(char *line, t_prsr *np)
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
}

void	prsr_sqr(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 10)
	{
		prsr_sqr_if(line, np);
		np->n++;
	}
	write_sqr(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr_cyl_if(char *line, t_prsr *np)
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
}

void	prsr_cyl(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 11)
	{
		prsr_cyl_if(line, np);
		np->n++;
	}
	write_cyl(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}
