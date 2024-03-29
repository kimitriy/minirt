/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:26:21 by rburton           #+#    #+#             */
/*   Updated: 2021/02/21 06:26:22 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	p2d_make(t_2d_point *out, int x, int y)
{
	out->x = x;
	out->y = y;
}

void	p_make(t_point *out, float x, float y, float z)
{
	out->x = x;
	out->y = y;
	out->z = z;
}

void	p_calc(t_point *out, t_vctr *vctr, t_point *tail)
{
	out->x = tail->x + vctr->xyz.x;
	out->y = tail->y + vctr->xyz.y;
	out->z = tail->z + vctr->xyz.z;
}

void	p_copy(t_point *out, t_point *in)
{
	out->x = in->x;
	out->y = in->y;
	out->z = in->z;
}

int		p_is_equal(t_point *p1, t_point *p2)
{
	if (p1->x == p2->x && p1->y == p2->y && p1->z == p2->z)
		return (1);
	else
		return (0);
}

void	v_xyz(t_vxyz *out, t_point *tail, t_point *head)
{
	out->x = head->x - tail->x;
	out->y = head->y - tail->y;
	out->z = head->z - tail->z;
}

void	v_lngth(t_vctr *nvctr)
{
	nvctr->lngth = sqrtf(powf(nvctr->xyz.x, 2) + powf(nvctr->xyz.y, 2) + powf(nvctr->xyz.z, 2));
}

void	v_n(t_vctr *nvctr)
{
	float	v_lngth;
	float	lngth_invrsn;

	v_lngth = sqrtf(powf(nvctr->nxyz.x, 2) + powf(nvctr->nxyz.y, 2) + powf(nvctr->nxyz.z, 2));
	// if (nvctr->nxyz.x == 0 && nvctr->nxyz.y == 0 & nvctr->nxyz.z == 0)
	if (roundf(v_lngth) != 1)
	{
		lngth_invrsn = 1 / nvctr->lngth;
		nvctr->nxyz.x = nvctr->xyz.x * lngth_invrsn;
		nvctr->nxyz.y = nvctr->xyz.y * lngth_invrsn;
		nvctr->nxyz.z = nvctr->xyz.z * lngth_invrsn;
	}
}

void	v_null(t_vctr *nvctr)
{
	nvctr->xyz.x = 0;
	nvctr->xyz.y = 0;
	nvctr->xyz.z = 0;
	nvctr->nxyz.x = 0;
	nvctr->nxyz.y = 0;
	nvctr->nxyz.z = 0;
	nvctr->lngth = 0;
}

void	v_fill(t_vctr *nvctr)
{
	if (nvctr->nxyz.x == 0 && nvctr->nxyz.y == 0 && nvctr->nxyz.z == 0)
	{
		v_lngth(nvctr);
		v_n(nvctr);
	}
	else if (nvctr->xyz.x == 0 && nvctr->xyz.y == 0 && nvctr->xyz.z == 0)
	{
		nvctr->xyz.x = nvctr->nxyz.x;
		nvctr->xyz.y = nvctr->nxyz.y;
		nvctr->xyz.z = nvctr->nxyz.z;
		v_lngth(nvctr);
	}
	else if (nvctr->xyz.x != nvctr->nxyz.x || nvctr->xyz.y != nvctr->nxyz.y || nvctr->xyz.z != nvctr->nxyz.z)
	{
		nvctr->nxyz.x = 0;
		nvctr->nxyz.y = 0;
		nvctr->nxyz.z = 0;
		v_lngth(nvctr);
		v_n(nvctr);
	}
}

void	v_make(t_vctr *out, t_point *tail, t_point *head)
{
	v_xyz(&out->xyz, tail, head);
	v_fill(out);
}

void	v_copy(t_vctr *out, t_vctr *in)
{
	out->xyz.x = in->xyz.x;
	out->xyz.y = in->xyz.y;
	out->xyz.z = in->xyz.z;
	out->nxyz.x = in->nxyz.x;
	out->nxyz.y = in->nxyz.y;
	out->nxyz.z = in->nxyz.z;
	out->lngth = in->lngth;
}

void	v_sum(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2)
{
	out->x = vctr1->x + vctr2->x;
	out->y = vctr1->y + vctr2->y;
	out->z = vctr1->z + vctr2->z;
}

void    v_n_prdct(t_vxyz *out, t_vxyz *vxyz, float num)
{
	out->x = vxyz->x * num;
	out->y = vxyz->y * num;
	out->z = vxyz->z * num;
}


float	v_d_prdct(t_vxyz *xyz1, t_vxyz *xyz2)
{
	float	dt_prdct;

	dt_prdct = xyz1->x * xyz2->x + xyz1->y * xyz2->y + xyz1->z * xyz2->z;
	return (dt_prdct);
}

float	v_x_point_prdct(t_vxyz *xyz, t_point *p)
{
	float	prdct;

	prdct = xyz->x * p->x + xyz->y * p->y + xyz->z * p->z;
	return (prdct);
}

void	v_crss_prdct(t_vxyz *out, t_vxyz *xyz1, t_vxyz *xyz2)
{
	out->x = xyz1->y * xyz2->z - xyz2->y * xyz1->z;
	out->y = -1 * (xyz1->x * xyz2->z - xyz2->x * xyz1->z);
	out->z = xyz1->x * xyz2->y - xyz2->x * xyz1->y;
}

float	v_angle(t_vctr *vctr1, t_vctr *vctr2)
{
    float	angle;
	float	dt_prdct;

	dt_prdct = v_d_prdct(&vctr1->xyz, &vctr2->xyz);
	angle = acosf(dt_prdct / (vctr1->lngth * vctr2->lngth));
	return (angle);
}

void	v_opposite(t_vctr *vctr)
{
	vctr->xyz.x = (-1) * vctr->xyz.x;
	vctr->xyz.y = (-1) * vctr->xyz.y;
	vctr->xyz.z = (-1) * vctr->xyz.z;
}

void	v_node(void)
{
	t_point	a;
	t_point	b;
	t_point	c;
	t_trngl	delta;

	p_make(&a, 1, 4, 0);
	p_make(&b, 4, 3, 1);
	p_make(&c, 2, 6, 3);

	delta.p1 = a;
	delta.p2 = b;
	delta.p3 = c;

	printf("A(%f, %f, %f)\n", a.x, a.y, a.z);
	printf("B(%f, %f, %f)\n", b.x, b.y, b.z);
	printf("C(%f, %f, %f)\n", c.x, c.y, c.z);
	printf("nrml2trngle(%f, %f, %f)\n", delta.n.nxyz.x, delta.n.nxyz.y, delta.n.nxyz.z);
}