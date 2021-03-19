/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:21:29 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 16:09:13 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	prsr_assist(char *line, t_prsr *np, char *field, int n)
{
	char	f;

	f = '0';
	while (np->j < n)
	{
		if ((ft_isdigit(line[np->i]) == 1 || line[np->i] == '.'
			|| line[np->i] == '-') && np->j < n)
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

void	write_p(t_point *p, t_prsr *np)
{
	p->x = ft_atof(np->x);
	p->y = ft_atof(np->y);
	p->z = ft_atof(np->z);
}

void	write_v(t_vctr *v, t_prsr *np)
{
	v->nxyz.x = ft_atof(np->nx);
	v->nxyz.y = ft_atof(np->ny);
	v->nxyz.z = ft_atof(np->nz);
	v_fill(v);
}

void	write_color(t_color *c, t_prsr *np)
{
	c->t = 0;
	c->r = ft_atoi(np->r);
	c->g = ft_atof(np->g);
	c->b = ft_atof(np->b);
}
