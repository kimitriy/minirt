/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:16:42 by rburton           #+#    #+#             */
/*   Updated: 2021/01/30 02:41:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

//La
void	l_ambnt(t_lum *lum)
{
	const float pi = 3.141593;
	float		beta;

	beta = v_angle(&lum->op, &lum->nrml) * 180 / pi;
	lum->angl = 180 - beta;
	lum->ka = (lum->angl >= 0 && lum->angl < 90) ? cos(lum->angl * pi / 180) : 0;
	lum->la = lum->alvl * lum->ka;
}

// void	l_ambnt(t_lum *lum)
// {
// 	t_vxyz new;
// 	new.x = 0;
// 	new.y = 1;
// 	new.z = 0;
// 	lum->la = 0.5 + lum->alvl * v_d_prdct(&lum->nrml.nxyz, &new);
// }

//Ld
void	l_dffse(t_lum *lum)
{
    float	fade;
	float	mx;
	
	lum->kd = 30;
	fade = lum->lvl / powf(lum->dst, 2);
	mx = max(0, v_d_prdct(&lum->ldir.nxyz, &lum->nrml.nxyz));
	lum->ld = lum->kd * fade * mx;
}

//Ls
void	l_spclr(t_lum *lum)
{
	float	fade;
	float	mx;

	lum->ks = 30;
	lum->p = 64;
	fade = lum->lvl / powf(lum->dst, 2);
	mx = max(0, v_d_prdct(&lum->nrml.nxyz, &lum->hvctr.nxyz));
	lum->ls = lum->ks * fade * pow(mx, lum->p);
}

void	l_all(t_lum *lum)
{
	l_ambnt(lum);
	l_dffse(lum);
	l_spclr(lum);
	lum->l = lum->la + lum->ld + lum->ls;
	lum->l = lum->l >= 1 ? 1 : lum->l;
}

void    lum_sphr(t_scn *lscn, t_ray *ray)
{
    t_lght  *lght;
    t_lum   lum;
    t_vctr  minus_op;
	t_sphr	*sphr;

	sphr = ray->nrst->content;
    lght = lscn->n_lght->content;
    lum.alvl = lscn->n_ambnt.lvl;
    lum.lvl = lght->lvl;
    lum.op = ray->vctr[ray->sgm]; //op vctr which is already calculated and stored in the ray struct
    nrml_sphr(&lum.nrml, ray, sphr); //makes nrml vctr
    v_make(&lum.ldir, &ray->hit_p[ray->sgm], &lght->p); //makes light direction vctr
    lum.dst = lum.ldir.lngth;
    v_null(&minus_op);
	minus_op.nxyz.x = (-1) * lum.op.nxyz.x;
    minus_op.nxyz.y = (-1) * lum.op.nxyz.y;
    minus_op.nxyz.z = (-1) * lum.op.nxyz.z;
    v_fill(&minus_op);
    v_sum(&lum.hvctr.xyz, &lum.ldir.nxyz, &minus_op.nxyz);
    v_fill(&lum.hvctr);
	l_all(&lum);
	color_copy(&ray->trgb, &sphr->trgb);
	color_modify(&ray->trgb, &lum);
}

/*
obj types:
p - pln;
s - sphr;
c - cyl;
q - sqr;
t - trngl;
*/

void	lum_node(t_scn *lscn, t_ray *ray)
{
	if (ray->obj == 's')
		lum_sphr(lscn, ray);
	// if (ray->obj = 'p')
	// 	lum_pln(lscn, ray);
	// if (ray->obj = 'c')
	// 	lum_cyl(lscn, ray);
	// if (ray->obj = 'q')
	// 	lum_sqr(lscn, ray);
	// if (ray->obj = 't')
	// 	lum_trngl(lscn, ray);
}