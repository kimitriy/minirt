/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_cyl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:41:12 by rburton           #+#    #+#             */
/*   Updated: 2021/03/10 07:41:20 by rburton          ###   ########.fr       */
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
	cln->_oxp1 = 0;
	cln->_oxp2 = 0;
	cln->angle = 0;
	cln->sin_alpha = 0;
	p_make(&cln->_o, 0, 0, 0);
	p_make(&cln->o_nb, 0, 0, 0);
	p_make(&cln->_c, 0, 0, 0);
	p_make(&cln->o, 0, 0, 0);
	p_make(&cln->c, 0, 0, 0);
	p_make(&cln->xp1, 0, 0, 0);
	p_make(&cln->xp2, 0, 0, 0);
	p_make(&cln->p, 0, 0, 0);
	v2d_null(&cln->_v_od);
	v2d_null(&cln->_v_oc);
	v_null(&cln->v_d);
	v_null(&cln->v_oxp1);
	v_null(&cln->v_oxp2);
	v_null(&cln->v_o_c);
	v_null(&cln->v_p_c);
	pln_null(&cln->pln);
}

void	cap_pln(t_cylon *cln, t_cyl *cyl)
{
	t_vctr	v_cc1;
	t_vctr	v_cc2;
	t_vctr	v_oc1;
	t_vctr	v_oc2;
	t_point	c1;
	t_point	c2;

	v_null(&v_cc1);
	v_null(&v_cc2);
	v_n_prdct(&v_cc1.xyz, &cyl->v.nxyz, (-1)*cyl->h/2);
	v_fill(&v_cc1);
	v_n_prdct(&v_cc2.xyz, &cyl->v.nxyz, cyl->h/2);
	v_fill(&v_cc2);
	p_calc(&c1, &v_cc1.xyz, &cyl->p);
	p_calc(&c2, &v_cc2.xyz, &cyl->p);
	v_null(&v_oc1);
	v_null(&v_oc2);
	v_make(&v_oc1, &cln->o, &c1);
	v_make(&v_oc2, &cln->o, &c2);
	if (v_oc1.lngth <= v_oc2.lngth)
	{
		p_copy(&cln->pln.p, &c1);
		v_copy(&cln->pln.v, &v_cc1);
	}
	else
	{
		p_copy(&cln->pln.p, &c2);
		v_copy(&cln->pln.v, &v_cc2);
	}
	v_n_prdct(&cyl->v.xyz, &cln->pln.v.xyz, -1);
	v_fill(&cyl->v);
}

void	cylon_fill(t_cylon *cln, t_ray *ray, t_cyl *cyl)
{
	p_copy(&cln->c, &cyl->p);
	p_copy(&cln->o, &ray->tail_p);
	v_copy(&cln->v_d, &ray->vctr[ray->sgm]);
}

void	cylon_cnvrse(t_cylon *cln, t_look_at *lkt)
{
	t_vctr		vtmp;

	mtrx4_x_point(&cln->o_nb, &lkt->m, &cln->o);
	v_null(&vtmp);
	mtrx4_x_vctr(&vtmp, &lkt->m, &cln->v_d.nxyz);
	cln->_v_od.xy.x = vtmp.xyz.x;
	cln->_v_od.xy.y = vtmp.xyz.y;
	v2d_lngth(&cln->_v_od);
	v_null(&vtmp);
	mtrx4_x_vctr(&vtmp, &lkt->m, &cln->v_o_c.xyz);
	cln->_v_oc.xy.x = vtmp.xyz.x;
	cln->_v_oc.xy.y = vtmp.xyz.y;
	v2d_lngth(&cln->_v_oc);
}

void	pln_calc(t_cylon *cln)
{
	t_plnx		plnx;

	plnx_null(&plnx);
	plnx = pln_equation(&cln->pln.p, &cln->o, &cln->pln.v, &cln->v_d); //4
	if (plnx.t != INFINITY && plnx.t > 0)
	{
		v_n_prdct(&cln->v_d.xyz, &cln->v_d.nxyz, plnx.t);
		v_fill(&cln->v_d);
		p_calc(&cln->p, &cln->v_d.xyz, &cln->o); // p - is a pointt where the ray intersects the pln
		v_make(&cln->v_p_c, &cln->p, &cln->pln.p);
	}
	p_copy(&cln->_o, &plnx._o);
	v_make(&cln->v_o_c, &cln->_o, &cln->pln.p);
	
}

void	cln_angles(t_cylon *cln)
{
	float tmp;

	cln->angle = v_angle(&cln->v_d, &cln->v_o_c) * 180 / M_PI;
	tmp = v_angle(&cln->v_d, &cln->pln.v);
	cln->sin_alpha = sinf(tmp);
}

void	ch_calc(t_cylon *cln, t_look_at *lkt)
{
	float	tmp;

	cylon_cnvrse(cln, lkt);
	tmp = v2d_pd_prdct(&cln->_v_od, &cln->_v_oc);
	cln->_ch = fabsf(tmp / cln->_v_od.lngth);
}

void	calc_nrml_cyl(t_cylon *cln, t_cyl *cyl)
{
	t_vctr	cxp;
	t_vctr	cm;
	float	tmp;
	float	r;

	r = cyl->d / 2;
	v_null(&cxp);
	v_null(&cm);
	if (cln->t1 != INFINITY && cln->t1 > 0 && cln->t1 <= cln->t2)
		v_make(&cxp, &cln->pln.p, &cln->xp1);
	else if (cln->t2 != INFINITY && cln->t2 > 0 && cln->t1 > cln->t2)
		v_make(&cxp, &cln->pln.p, &cln->xp2);
	tmp = sqrt(powf(cxp.lngth, 2) - powf(r, 2));
	v_n_prdct(&cm.xyz, &cyl->v.nxyz, tmp);
	v_fill(&cm);
	v_sbtrct(&cyl->n.xyz, &cxp.xyz, &cm.xyz);
	v_fill(&cyl->n);
}

void	xp_cyl(t_cylon *cln, t_cyl *cyl)
{
	if (cln->t1 != INFINITY)
	{
		v_n_prdct(&cln->v_oxp1.xyz, &cln->v_d.nxyz, cln->t1);
		v_fill(&cln->v_oxp1);
		p_calc(&cln->xp1, &cln->v_oxp1.xyz, &cln->o);
	}
	if (cln->t2 != INFINITY)
	{
		v_n_prdct(&cln->v_oxp2.xyz, &cln->v_d.nxyz, cln->t2);
		v_fill(&cln->v_oxp2);
		p_calc(&cln->xp2, &cln->v_oxp2.xyz, &cln->o);
	}
}

void	case1(t_cylon *cln, t_cyl *cyl)
{
	cln->_oxp1 = cln->_oh + cln->_hxp;
	cln->t1 = 0.999995 * cln->_oxp1 / cln->sin_alpha;
	xp_cyl(cln, cyl);
}

void	case2(t_cylon *cln, t_cyl *cyl)
{
	cln->_oxp1 = cln->_oh + cln->_hxp;
	cln->t1 = 0.999995 * cln->_oxp1 / cln->sin_alpha;
	xp_cyl(cln, cyl);
}

void	case3(t_cylon *cln, t_cyl *cyl)
{
	cln->_oxp1 = cln->_oh - cln->_hxp;
	cln->_oxp2 = cln->_oh + cln->_hxp;
	cln->t1 = 0.999995 * cln->_oxp1 / cln->sin_alpha;
	cln->t2 = 0.999995 * cln->_oxp2 / cln->sin_alpha;
	xp_cyl(cln, cyl);
}

void	case4(t_cylon *cln, t_cyl *cyl)
{
	cln->_oxp1 = cln->_oh;
	cln->t1 = 0.999995 * cln->_oxp1 / cln->sin_alpha;
	xp_cyl(cln, cyl);
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

void	find_roots(t_cylon *cln, t_cyl *cyl, t_look_at *lkt)
{
	float	r;

	r = cyl->d / 2;
	cln->_oh = sqrtf(powf(cln->v_o_c.lngth, 2) - powf(cln->_ch, 2));
	cln->_hxp = sqrtf(powf(r, 2) - powf(cln->_ch, 2));
	if (cln->v_o_c.lngth <= r && cln->v_p_c.lngth <= r && cln->o_nb.z < 0)
		case1(cln, cyl);
	else if (cln->v_o_c.lngth <= r && /*cln->v_p_c.lngth > r && */cln->o_nb.z >= 0 && cln->o_nb.z <= cyl->h)
		case2(cln, cyl);
	else if (cln->v_o_c.lngth > r)
	{
		if (cln->angle < 90)
		{
			if (cln->_ch < r)
				case3(cln, cyl);
			else if (cln->_ch == r)
				case4(cln, cyl);
			else
				cylon_null(cln);
		}
		else if (cln->angle <= 90)
			cylon_null(cln);
	}
	else if (cln->v_o_c.lngth <= r && cln->v_p_c.lngth > r)
		cylon_null(cln);
	is_on_cyl(cln, cyl, lkt);
	// calc_nrml_cyl(cln, cyl);
}

void	cylon_make(t_cylon *cln, t_ray *ray, t_cyl *cyl)
{
	t_look_at	lkt;
	
	cylon_fill(cln, ray, cyl);
	cap_pln(cln, cyl); //1
	look_at_mtrx(&lkt, &cyl->v, &cln->pln.p); //2
	pln_calc(cln);
	ch_calc(cln, &lkt);
	cln_angles(cln);
	find_roots(cln, cyl, &lkt);
	if ((cln->t1 != INFINITY || cln->t2 != INFINITY) && ray->sgm == 0)
	{	
		if (ray->sgm == 0)
			calc_nrml_cyl(cln, cyl);
		nrml_cyl(cyl, ray);
	}
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
		ray->dist = cln.t1;
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