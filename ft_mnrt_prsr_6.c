/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:06:11 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:08:53 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	prsr_trngl_if(char *line, t_prsr *np)
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
}

void	prsr_trngl(char *line, t_scn *nscn, t_prsr *np)
{
	while (line[np->i] && np->n < 12)
	{
		prsr_trngl_if(line, np);
		np->n++;
	}
	write_trngl(nscn, np);
	nprsr_reset_counters(np);
	nprsr_nullt_fields(np);
}

void	prsr(char **scn_arr, int size, t_scn *nscn, t_prsr *np)
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
