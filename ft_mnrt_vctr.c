/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_vctr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:26:21 by rburton           #+#    #+#             */
/*   Updated: 2021/01/16 16:48:20 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

// makes point
t_point	*p_make(float x, float y, float z)
{
	t_point	*new_point;
	
	if (!(new_point = (t_point*)malloc(1 * sizeof(t_point))))
		return NULL;
	new_point->x = x;
	new_point->y = y;
	new_point->z = z;
	return (new_point);
}


void	v_xyz(t_vctr *vctr, t_point *tail, t_point *head)
{
	vctr->x = head->x - tail->x;
	vctr->y = head->y - tail->y;
	vctr->z = head->z - tail->z;
}

void	v_lngth(t_vctr *vctr)
{
	vctr->lngth = sqrtf(powf(vctr->x, 2) + powf(vctr->y, 2) + powf(vctr->z, 2));
}

void	v_nxyz(t_vctr *vctr)
{
	float	lngth_invrsn;

	lngth_invrsn = 1 / vctr->lngth;
	vctr->nx = vctr->x * lngth_invrsn;
	vctr->ny = vctr->y * lngth_invrsn;
	vctr->nz = vctr->z * lngth_invrsn;
}

//makes vector
t_vctr	*v_make(t_point *tail, t_point *head)
{
	t_vctr *new_vctr;

	if (!(new_vctr = (t_vctr*)malloc(1 * sizeof(t_vctr))))
		return NULL;
	v_xyz(new_vctr, tail, head);
	v_lngth(new_vctr);
	v_nxyz(new_vctr);
	return (new_vctr);
}

t_vctr	*v_sum(t_vctr *vctr1, t_vctr *vctr2)
{
	t_vctr *new_vctr;
	
	if (!(new_vctr = (t_vctr*)malloc(1 * sizeof(t_vctr))))
		return NULL;
	new_vctr->x = vctr1->x + vctr2->x;
	new_vctr->y = vctr1->y + vctr2->y;
	new_vctr->z = vctr1->z + vctr2->z;
	v_lngth(new_vctr);
	v_nxyz(new_vctr);
	return (new_vctr);
}

void    v_n_prdct(t_vctr *vctr, float num)
{
	vctr->x = vctr->x * num;
	vctr->y = vctr->y * num;
	vctr->z = vctr->z * num;
	v_lngth(vctr);
	v_nxyz(vctr);
}

void    nv_n_prdct(t_vctr *vctr, float num)
{
	vctr->x = vctr->nx * num;
	vctr->y = vctr->ny * num;
	vctr->z = vctr->nz * num;
	v_lngth(vctr);
	v_nxyz(vctr);
}

float	v_dt_prdct(t_vctr *vctr1, t_vctr *vctr2)
{
	float	dt_prdct;

	dt_prdct = vctr1->x * vctr2->x + vctr1->y * vctr2->y + vctr1->z * vctr2->z;
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

	printf("A1A2 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A2->x, A1A2->y, A1A2->z, A1A2->nx, A1A2->ny, A1A2->nz, A1A2->lngth);

	//v_n_prdct(A1A2, 1.5);

	dot_product = v_dt_prdct(A1A2, A1A3);

	angle = v_angle(A1A2, A1A3) * 180 / M_PI;

	printf("A1A2x1.5 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A2->x, A1A2->y, A1A2->z, A1A2->nx, A1A2->ny, A1A2->nz, A1A2->lngth);
	printf("A1A3 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A3->x, A1A3->y, A1A3->z, A1A3->nx, A1A3->ny, A1A3->nz, A1A3->lngth);
	printf("A1A4 (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", A1A4->x, A1A4->y, A1A4->z, A1A4->nx, A1A4->ny, A1A4->nz, A1A4->lngth);
	printf("vsum (x:%f, y:%f, z:%f / nx:%f, ny:%f, nz:%f / lngth:%f)\n", vsum->x, vsum->y, vsum->z, vsum->nx, vsum->ny, vsum->nz, vsum->lngth);
	printf("dot_product:%f\n", dot_product);
	printf("angle:%f\n", angle);
}