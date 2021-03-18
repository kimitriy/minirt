/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_bmp_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:26:54 by rburton           #+#    #+#             */
/*   Updated: 2021/03/18 17:30:25 by rburton          ###   ########.fr       */
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
