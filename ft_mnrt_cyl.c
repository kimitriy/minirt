/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:41:12 by rburton           #+#    #+#             */
/*   Updated: 2021/02/28 22:57:33 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	cylon_null(t_cylon *cln)
{
	cln->_CH = INFINITY;
	cln->t1 = INFINITY;
	cln->t2 = INFINITY;
	cln->_OH = 0;
	cln->_HXP = 0;
	cln->alpha = 0;
	p2d_make(&cln->_RO, 0, 0);
	p2d_make(&cln->_C, 0, 0);
	p2d_make(&cln->_D, 0, 0);
	p_make(&cln->RO, 0, 0, 0);
	p_make(&cln->C, 0, 0, 0);
	p_make(&cln->XP1, 0, 0, 0);
	p_make(&cln->XP2, 0, 0, 0);
	v2d_null(&cln->_vD);
	v2d_null(&cln->_vOC);
	v_null(&cln->vD);
	v_null(&cln->vOXP1);
	v_null(&cln->vOXP2);
	v_null(&cln->vCXP1);
	v_null(&cln->vCXP2);
	v_null(&cln->vCM1);
	v_null(&cln->vCM2);
	cln->xp_on = '\0';
}

void	cylon_cnvrse(t_cylon *cln, t_look_at *lkt)
{
	t_point		ptmp;
	t_vctr		vtmp;

	p_make(&ptmp, 0, 0, 0);
	mtrx4_x_point(&ptmp, &lkt->m, &cln->RO);
	cln->_RO.x = ptmp.x;
	cln->_RO.y = ptmp.y;
	p_make(&ptmp, 0, 0, 0);
	mtrx4_x_point(&ptmp, &lkt->m, &cln->C);
	cln->_C.x = ptmp.x;
	cln->_C.y = ptmp.y;
	v_null(&vtmp);
	mtrx4_x_vctr(&vtmp, &lkt->m, &cln->vD.xyz);
	cln->_vD.xy.x = vtmp.nxyz.x;
	cln->_vD.xy.y = vtmp.nxyz.y;
	v2d_lngth(&cln->_vD);
}

void	cylon_make(t_cylon *cln, t_ray *ray, t_cyl *cyl)
{
	t_look_at	lkt;

	look_at_mtrx(&lkt, &cyl->v, &cyl->p);
	p_copy(&cln->C, &cyl->p);
	v_copy(&cln->vD, &ray->vctr[ray->sgm]);
	cylon_cnvrse(cln, &lkt);
	v2d_make(&cln->_vOC, &cln->_RO, &cln->_C);
	cln->_CH = fabsf(v2d_pd_prdct(&cln->_vD, &cln->_vOC) / cln->_vD.lngth);
	if (cln->_CH > 0 && cln->_CH <= cyl->d/2)
	{
		cln->xp_on = '+';
		cln->_OH = sqrtf(powf(cln->_vOC.lngth, 2) - powf(cln->_CH, 2));
		cln->alpha = v_angle(&cyl->v, &cln->vD);
		if (cln->_CH == cyl->d/2)
			cln->t1 = cln->_OH / sinf(cln->alpha);
		else
		{
			cln->_HXP = sqrtf(powf(cyl->d / 2, 2) - powf(cln->_CH, 2));
			cln->t1 = (cln->_OH - cln->_HXP) / sinf(cln->alpha);
			cln->t2 = (cln->_OH + cln->_HXP) / sinf(cln->alpha);
		}
	}
	cylon_make2(cln, ray, cyl, &lkt);
}

void	is_on_cyl(t_cylon *cln, t_cyl *cyl, t_look_at *lkt)
{
	t_point	tmp1;
	t_point	tmp2;

	mtrx4_x_point(&tmp1, &lkt->m, &cln->XP1);
	mtrx4_x_point(&tmp2, &lkt->m, &cln->XP2);
	if ((tmp1.z < 0 || tmp1.z > cyl->h) && (tmp2.z < 0 || tmp2.z > cyl->h))
		cylon_null(cln);
	else if ((tmp1.z < 0 || tmp1.z > cyl->h) && (tmp2.z >= 0 && tmp2.z <= cyl->h))
	{
		cln->t1 = INFINITY;
		p_make(&cln->XP1, 0, 0, 0);
		v_null(&cln->vOXP1);
	}
	else if ((tmp1.z >= 0 && tmp1.z <= cyl->h) && (tmp2.z < 0 || tmp2.z > cyl->h))
	{
		cln->t2 = INFINITY;
		p_make(&cln->XP2, 0, 0, 0);
		v_null(&cln->vOXP2);
	}
}

void	cylon_make2(t_cylon *cln, t_ray *ray, t_cyl *cyl, t_look_at *lkt)
{
	if (cln->xp_on == '+')
	{
		v_n_prdct(&cln->vOXP1.xyz, &cln->vD.nxyz, cln->t1);
		v_fill(&cln->vOXP1);
		p_calc(&cln->XP1, &cln->vOXP1, &cln->RO);
		if (cln->t2 != 0)
		{
			v_n_prdct(&cln->vOXP2.xyz, &cln->vD.nxyz, cln->t2);
			v_fill(&cln->vOXP2);
			p_calc(&cln->XP2, &cln->vOXP2, &cln->RO);
		}
		//XP1 XP2 пересчитать через lkt проверить что координата z > 0 && z <= 0 + h
		is_on_cyl(cln, cyl, lkt);
		cylon_make3(cln, cyl);
		nrml_cyl(cyl, ray); //необходимо передавать в эту функцию только ту нормаль которую видно
	}
}

void	cylon_make3(t_cylon *cln, t_cyl *cyl)
{	
	if (cln->t1 != INFINITY)
	{
		v_make(&cln->vCXP1, &cln->C, &cln->XP1);
		v_n_prdct(&cln->vCM1.xyz, &cyl->v.nxyz, sqrtf(powf(cln->vCXP1.lngth, 2) - powf(cyl->d / 2, 2)));
		v_fill(&cln->vCM1);
		v_sbtrct(&cyl->n1.xyz, &cln->vCXP1.xyz, &cln->vCM1.xyz);
		v_fill(&cyl->n1);
	}
	if (cln->t2 != INFINITY)
	{
		v_make(&cln->vCXP2, &cln->C, &cln->XP2);
		v_n_prdct(&cln->vCM2.xyz, &cyl->v.nxyz, sqrtf(powf(cln->vCXP2.lngth, 2) - powf(cyl->d / 2, 2)));
		v_fill(&cln->vCM2);
		v_sbtrct(&cyl->n2.xyz, &cln->vCXP2.xyz, &cln->vCM2.xyz);
		v_fill(&cyl->n2);
	}
}

void	cyl_intrsct(t_scn *lscn, t_cyl *cyl, t_ray *ray)
{
	t_cylon		cln;

	cylon_null(&cln);
	cylon_make(&cln, ray, cyl);
	if (cln.xp_on == '+' && ray->sgm == 0)
	{
		ray->obj = 'c';
		ray->nrst = lscn->n_cyl;
		if (cln.t2 == 0)
			ray->dist = cln.t1;
		else
			ray->dist = cln.t1 < cln.t2 ? cln.t1 : cln.t2;
		if (ray->dist == cln.t1)
		{
			v_copy(&ray->vctr[0], &cln.vOXP1);
			p_copy(&ray->hit_p, &cln.XP1);
		}
		else
		{
			v_copy(&ray->vctr[0], &cln.vOXP2);
			p_copy(&ray->hit_p, &cln.XP2);
		}
	}
	if (cln.xp_on == '+' && ray->sgm == 1 && ray->shdw != 'y')
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