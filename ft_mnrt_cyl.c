/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:41:12 by rburton           #+#    #+#             */
/*   Updated: 2021/03/07 04:15:51 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cylon_null(t_cylon *cln)
{
	cln->_ch = INFINITY;
	cln->t1 = INFINITY;
	cln->t2 = INFINITY;
	cln->_oh = 0;
	cln->_hxp = 0;
	cln->angle = 0;
	cln->alpha = 0;
	p2d_make(&cln->_ro, 0, 0);
	p2d_make(&cln->_c, 0, 0);
	p_make(&cln->ro, 0, 0, 0);
	p_make(&cln->c, 0, 0, 0);
	p_make(&cln->xp1, 0, 0, 0);
	p_make(&cln->xp2, 0, 0, 0);
	p_make(&cln->p, 0, 0, 0);
	v2d_null(&cln->_v_d);
	v2d_null(&cln->_v_oc);
	v_null(&cln->v_d);
	v_null(&cln->v_oxp1);
	v_null(&cln->v_oxp2);
	v_null(&cln->v_cxp1);
	v_null(&cln->v_cxp2);
	v_null(&cln->v_cm1);
	v_null(&cln->v_cm2);
	v_null(&cln->v_cp);
	pln_null(&cln->pln);
}

void	cylon_cnvrse(t_cylon *cln, t_look_at *lkt)
{
	t_point		ptmp;
	t_vctr		vtmp;

	p_make(&ptmp, 0, 0, 0);
	mtrx4_x_point(&ptmp, &lkt->m, &cln->ro);
	cln->_ro.x = ptmp.x;
	cln->_ro.y = ptmp.y;
	p_make(&ptmp, 0, 0, 0);
	mtrx4_x_point(&ptmp, &lkt->m, &cln->c);
	cln->_c.x = ptmp.x;
	cln->_c.y = ptmp.y;
	v_null(&vtmp);
	mtrx4_x_vctr(&vtmp, &lkt->m, &cln->v_d.xyz);
	cln->_v_d.xy.x = vtmp.nxyz.x;
	cln->_v_d.xy.y = vtmp.nxyz.y;
	v2d_lngth(&cln->_v_d);
}

void	calc_roots1(t_cylon *cln, t_cyl *cyl)
{
	cln->_ch = fabsf(v2d_pd_prdct(&cln->_v_d, &cln->_v_oc) / cln->_v_d.lngth);
	if (cln->_ch >= 0 && cln->_ch <= cyl->d/2)
	{
		cln->_oh = sqrtf(powf(cln->_v_oc.lngth, 2) - powf(cln->_ch, 2));
		if (cln->_ch == cyl->d/2)
		{	
			cln->t1 = 0.999995 * cln->_oh / sinf(cln->alpha);
			cln->t1 = cln->t1 < 0 ? INFINITY : cln->t1;
		}
		else
		{
			cln->_hxp = sqrtf(powf(cyl->d / 2, 2) - powf(cln->_ch, 2));
			cln->t1 = 0.999995 * (cln->_oh - cln->_hxp) / sinf(cln->alpha);
			cln->t1 = cln->t1 < 0 ? INFINITY : cln->t1;
			cln->t2 = 0.999995 * (cln->_oh + cln->_hxp) / sinf(cln->alpha);
			cln->t2 = cln->t2 < 0 ? INFINITY : cln->t2;
		}
	}
	else
		cylon_null(cln);
}

void	calc_roots2(t_cylon *cln, t_cyl *cyl, t_look_at	*lkt)
{
	float	vctr_projection;

	p_copy(&cln->pln.p, &cyl->p);
	v_copy(&cln->pln.v, &lkt->vF);
	cln->t1 = pln_equation(&cln->pln.p, &cln->ro, &cln->pln.v, &cln->v_d);
	v_n_prdct(&cln->v_d.xyz, &cln->v_d.nxyz, cln->t1);
	v_fill(&cln->v_d);
	p_calc(&cln->p, &cln->v_d, &cln->ro); // p - is a pointt where the ray intersects the pln
	v_make(&cln->v_cp, &cln->c, &cln->p);
	if (cln->v_cp.lngth <= cyl->d / 2)
	{
		cln->_ch = fabsf(v2d_pd_prdct(&cln->_v_d, &cln->_v_oc) / cln->_v_d.lngth);
		cln->_oh = sqrtf(powf(cln->_v_oc.lngth, 2) - powf(cln->_ch, 2));
		cln->_hxp = sqrtf(powf(cyl->d / 2, 2) - powf(cln->_ch, 2));
		vctr_projection = cln->_oh + cln->_hxp;
		cln->t1 = 0.999995 * vctr_projection / sinf(cln->alpha);
		cln->t1 = cln->t1 < 0 ? INFINITY : cln->t1;
	}
	else
		cylon_null(cln);
}

void	cylon_make(t_cylon *cln, t_ray *ray, t_cyl *cyl)
{
	t_look_at	lkt;
	
	look_at_mtrx(&lkt, &cyl->v, &cyl->p);
	cylon_make1(cln, ray, cyl, &lkt);
	if (cln->_v_oc.lngth > cyl->d / 2 && cln->angle >= 90)
		cylon_null(cln);
	else
	{
		if (cln->_v_oc.lngth > cyl->d / 2 && cln->angle < 90)
		{
			calc_roots1(cln, cyl);
		}
		else if (cln->_v_oc.lngth <= cyl->d / 2)
		{
			calc_roots2(cln, cyl, &lkt);
		}
		cylon_make2(cln, ray, cyl, &lkt);
	}
}

void	is_on_cyl(t_cylon *cln, t_cyl *cyl, t_look_at *lkt)
{
	t_point	tmp1;
	t_point	tmp2;

	mtrx4_x_point(&tmp1, &lkt->m, &cln->xp1);
	mtrx4_x_point(&tmp2, &lkt->m, &cln->xp2);
	if ((tmp1.z < 0 || tmp1.z > cyl->h) && (tmp2.z < 0 || tmp2.z > cyl->h))
		cylon_null(cln);
	else if ((tmp1.z < 0 || tmp1.z > cyl->h) && (tmp2.z >= 0 && tmp2.z <= cyl->h))
	{
		cln->t1 = INFINITY;
		p_make(&cln->xp1, 0, 0, 0);
		v_null(&cln->v_oxp1);
	}
	else if ((tmp1.z >= 0 && tmp1.z <= cyl->h) && (tmp2.z < 0 || tmp2.z > cyl->h))
	{
		cln->t2 = INFINITY;
		p_make(&cln->xp2, 0, 0, 0);
		v_null(&cln->v_oxp2);
	}
}

void	cylon_make1(t_cylon *cln, t_ray *ray, t_cyl *cyl, t_look_at *lkt)
{
	float 		d_prdct;
	float		mul_length;
	float		cos_angle;

	p_copy(&cln->c, &cyl->p);
	p_copy(&cln->ro, &ray->tail_p);
	v_copy(&cln->v_d, &ray->vctr[ray->sgm]);
	cylon_cnvrse(cln, lkt);
	v2d_make(&cln->_v_oc, &cln->_ro, &cln->_c);
	d_prdct = v2d_d_prdct(&cln->_v_d.xy, &cln->_v_oc.xy);
	mul_length = cln->_v_d.lngth * cln->_v_oc.lngth;
	cos_angle = min_2floats(d_prdct / mul_length, 1);
	cln->angle = acosf(cos_angle) * 180 / M_PI;
	cln->alpha = v_angle(&cyl->v, &cln->v_d);
}

void	cylon_make2(t_cylon *cln, t_ray *ray, t_cyl *cyl, t_look_at *lkt)
{
	if (cln->t1 > 0 && cln->t1 != INFINITY)
	{
		v_n_prdct(&cln->v_oxp1.xyz, &cln->v_d.nxyz, cln->t1);
		v_fill(&cln->v_oxp1);
		p_calc(&cln->xp1, &cln->v_oxp1, &cln->ro);
	}
	if (cln->t2 > 0 && cln->t2 != INFINITY)
	{
		v_n_prdct(&cln->v_oxp2.xyz, &cln->v_d.nxyz, cln->t2);
		v_fill(&cln->v_oxp2);
		p_calc(&cln->xp2, &cln->v_oxp2, &cln->ro);
	}
	//xp1 xp2 пересчитать через lkt проверить что координата z > 0 && z <= 0 + h
	is_on_cyl(cln, cyl, lkt);
	cylon_make3(cln, cyl);
	nrml_cyl(cyl, ray); //необходимо передавать в эту функцию только ту нормаль которую видно
}

void	cylon_make3(t_cylon *cln, t_cyl *cyl)
{	
	if (cln->t1 != INFINITY && fabsf(cln->t1) > 0 && cln->t1 <= cln->t2)
	{
		v_make(&cln->v_cxp1, &cln->c, &cln->xp1);
		v_n_prdct(&cln->v_cm1.xyz, &cyl->v.nxyz, sqrtf(powf(cln->v_cxp1.lngth, 2) - powf(cyl->d / 2, 2)));
		v_fill(&cln->v_cm1);
		v_sbtrct(&cyl->n.xyz, &cln->v_cxp1.xyz, &cln->v_cm1.xyz);
	}
	else if (cln->t2 != INFINITY && fabsf(cln->t2) > 0 && cln->t2 < cln->t1)
	{
		v_make(&cln->v_cxp2, &cln->c, &cln->xp2);
		v_n_prdct(&cln->v_cm2.xyz, &cyl->v.nxyz, sqrtf(powf(cln->v_cxp2.lngth, 2) - powf(cyl->d / 2, 2)));
		v_fill(&cln->v_cm2);
		v_sbtrct(&cyl->n.xyz, &cln->v_cxp2.xyz, &cln->v_cm2.xyz);
	}
	else
		cylon_null(cln);
	v_fill(&cyl->n);
}

void	cyl_intrsct(t_scn *lscn, t_cyl *cyl, t_ray *ray)
{
	t_cylon		cln;

	cylon_null(&cln);
	cylon_make(&cln, ray, cyl);
	if (min_2floats(cln.t1, cln.t2) < ray->dist && ray->sgm == 0)
	{
		ray->obj = 'c';
		ray->nrst = lscn->n_cyl;
		if (cln.t1 != INFINITY && cln.t2 == INFINITY)
			ray->dist = cln.t1;
		else if (cln.t1 == INFINITY && cln.t2 != INFINITY)
			ray->dist = cln.t2;
		else if (cln.t1 != INFINITY && cln.t2 != INFINITY)
			ray->dist = cln.t1 < cln.t2 ? cln.t1 : cln.t2;
		if (ray->dist == cln.t1)
		{
			v_copy(&ray->vctr[0], &cln.v_oxp1);
			p_copy(&ray->hit_p, &cln.xp1);
		}
		else
		{
			v_copy(&ray->vctr[0], &cln.v_oxp2);
			p_copy(&ray->hit_p, &cln.xp2);
		}
	}
	if (ray->sgm == 1 && ray->shdw != 'y' && min_2floats(cln.t1, cln.t2) < ray->vctr[1].lngth)
		ray->shdw = 'y';
}

void 	check_cyls(t_scn *lscn, t_ray *ray)
{
	int		i;
	t_cyl	*cyl;

	i = 0;
	lscn->n_cyl = lscn->frst_cyl;
	while (i < lscn->n_cntr.cyl)
	{
		cyl = lscn->n_cyl->content;
		cyl_intrsct(lscn, cyl, ray);
		if (lscn->n_cyl->next != NULL)
			lscn->n_cyl = lscn->n_cyl->next;
		i++;
	}
}