/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_pln_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:44:01 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 13:44:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray)
{
	float	t;

	nrml_pln(pln, ray);
	t = pln_equation(&pln->p, &ray->tail_p, &pln->v, &ray->vctr[ray->sgm]).t;
	if (t > 0.00001 && t < ray->dist && ray->sgm == 0)
	{
		ray->dist = t;
		ray->obj = 'p';
		ray->nrst = lscn->n_pln;
		v_n_prdct(&ray->vctr[0].xyz, &ray->vctr[ray->sgm].nxyz, ray->dist);
		v_fill(&ray->vctr[0]);
		p_calc(&ray->hit_p, &ray->vctr[0].xyz, &ray->tail_p);
	}
	if (ray->sgm == 1 && t > 0 && ray->shdw != 'y' && t < ray->vctr[1].lngth)
		ray->shdw = 'y';
}

void	check_plns(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_pln	*pln;

	i = 0;
	lscn->n_pln = lscn->frst_pln;
	while (i < lscn->n_cntr.pln)
	{
		pln = lscn->n_pln->content;
		pln->v.xyz.x = 0;
		pln->v.xyz.y = 0;
		pln->v.xyz.z = 0;
		v_fill(&pln->v);
		pln_intrsct(lscn, pln, ray);
		if (lscn->n_pln->next != NULL)
			lscn->n_pln = lscn->n_pln->next;
		i++;
	}
}
