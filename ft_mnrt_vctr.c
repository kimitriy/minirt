/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:26:21 by rburton           #+#    #+#             */
/*   Updated: 2021/01/18 20:47:05 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

// makes point
// t_point	*p_make(float x, float y, float z)
// {
// 	t_point	*new_point;
	
// 	if (!(new_point = (t_point*)malloc(1 * sizeof(t_point))))
// 		return NULL;
// 	new_point->x = x;
// 	new_point->y = y;
// 	new_point->z = z;
// 	return (new_point);
// }

void	p_make(t_point *output, float x, float y, float z)
{
	output->x = x;
	output->y = y;
	output->z = z;
}

void	v_xyz(t_vctr *vctr, t_point *tail, t_point *head)
{
	vctr->xyz.x = head->x - tail->x;
	vctr->xyz.y = head->y - tail->y;
	vctr->xyz.z = head->z - tail->z;
}

void	v_lngth(t_vctr *vctr)
{
	vctr->lngth = sqrtf(powf(vctr->xyz.x, 2) + powf(vctr->xyz.y, 2) + powf(vctr->xyz.z, 2));
}

void	v_nxyz(t_vctr *vctr)
{
	float	lngth_invrsn;

	lngth_invrsn = 1 / vctr->lngth;
	vctr->nrmlsd.x = vctr->xyz.x * lngth_invrsn;
	vctr->nrmlsd.y = vctr->xyz.y * lngth_invrsn;
	vctr->nrmlsd.z = vctr->xyz.z * lngth_invrsn;
}

//makes vector
// t_vctr	*v_make(t_point *tail, t_point *head)
// {
// 	t_vctr *new_vctr;

// 	if (!(new_vctr = (t_vctr*)malloc(1 * sizeof(t_vctr))))
// 		return NULL;
// 	v_xyz(new_vctr, tail, head);
// 	v_lngth(new_vctr);
// 	v_nxyz(new_vctr);
// 	return (new_vctr);
// }

void	v_make(t_vctr *output, t_point *tail, t_point *head)
{
	v_xyz(output, tail, head);
	v_lngth(output);
	v_nxyz(output);
}

t_vctr	*v_sum(t_vctr *vctr1, t_vctr *vctr2)
{
	t_vctr *new_vctr;
	
	if (!(new_vctr = (t_vctr*)malloc(1 * sizeof(t_vctr))))
		return NULL;
	new_vctr->xyz.x = vctr1->xyz.x + vctr2->xyz.x;
	new_vctr->xyz.y = vctr1->xyz.y + vctr2->xyz.y;
	new_vctr->xyz.z = vctr1->xyz.z + vctr2->xyz.z;
	v_lngth(new_vctr);
	v_nxyz(new_vctr);
	return (new_vctr);
}

void    v_n_prdct(t_vctr *vctr, float num)
{
	vctr->xyz.x = vctr->xyz.x * num;
	vctr->xyz.y = vctr->xyz.y * num;
	vctr->xyz.z = vctr->xyz.z * num;
	v_lngth(vctr);
	v_nxyz(vctr);
}

void    nv_n_prdct(t_vctr *vctr, float num)
{
	vctr->xyz.x = vctr->nrmlsd.x * num;
	vctr->xyz.y = vctr->nrmlsd.y * num;
	vctr->xyz.z = vctr->nrmlsd.z * num;
	v_lngth(vctr);
	v_nxyz(vctr);
}

float	v_dt_prdct(t_vxyz *xyz1, t_vxyz *xyz2)
{
	float	dt_prdct;

	dt_prdct = xyz1->x * xyz2->x + xyz1->y * xyz2->y + xyz1->z * xyz2->z;
	return (dt_prdct);
}

float	v_angle(t_vctr *vctr1, t_vctr *vctr2)
{
    float	angle;
	float	dt_prdct;

	dt_prdct = v_dt_prdct(vctr1, vctr2);
	angle = acosf(dt_prdct / (vctr1->lngth * vctr2->lngth));
	return (angle);
}

void	v_node(void)
{
	t_point	*a1;
	t_point	*a2;
	t_point	*a3;
	t_point	*a4;
	//t_point	*s;

	t_vctr	*A1A2;
	t_vctr	*A1A3;
	t_vctr	*A1A4;
	t_vctr	*vsum;

	float	dot_product;
	float	angle;

	a1 = p_make(10, 5, -4);
	a2 = p_make(-8, 6, 3);
	a3 = p_make(1, 1, -1);
	a4 = p_make(0, 0, 1);
	//s = p_make();

	A1A2 = v_make(a1, a2);
	A1A3 = v_make(a1, a3);
	A1A4 = v_make(a1, a4);

	vsum = v_sum(A1A2, A1A3);

	printf("A1A2 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A2->xyz.x, A1A2->xyz.y, A1A2->xyz.z, A1A2->nrmlsd.x, A1A2->nrmlsd.y, A1A2->nrmlsd.z, A1A2->lngth);

	//v_n_prdct(A1A2, 1.5);

	dot_product = v_dt_prdct(A1A2, A1A3);

	angle = v_angle(A1A2, A1A3) * 180 / M_PI;

	printf("A1A2x1.5 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A2->xyz.x, A1A2->xyz.y, A1A2->xyz.z, A1A2->nrmlsd.x, A1A2->nrmlsd.y, A1A2->nrmlsd.z, A1A2->lngth);
	printf("A1A3 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A3->xyz.x, A1A3->xyz.y, A1A3->xyz.z, A1A3->nrmlsd.x, A1A3->nrmlsd.y, A1A3->nrmlsd.z, A1A3->lngth);
	printf("A1A4 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A4->xyz.x, A1A4->xyz.y, A1A4->xyz.z, A1A4->nrmlsd.x, A1A4->nrmlsd.y, A1A4->nrmlsd.z, A1A4->lngth);
	printf("vsum (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", vsum->xyz.x, vsum->xyz.y, vsum->xyz.z, vsum->nrmlsd.x, vsum->nrmlsd.y, vsum->nrmlsd.z, vsum->lngth);
	printf("dot_product:%f\n", dot_product);
	printf("angle:%f\n", angle);
}