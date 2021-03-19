/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_mtrx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:47:37 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 13:33:57 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	mtrx4_x_point(t_point *out, t_mtrx4x4 *mtrx, t_point *in)
{
	out->x = mtrx->m[0][0] * in->x + mtrx->m[0][1] * in->y +
		mtrx->m[0][2] * in->z + mtrx->m[0][3] * 1;
	out->y = mtrx->m[1][0] * in->x + mtrx->m[1][1] * in->y +
		mtrx->m[1][2] * in->z + mtrx->m[1][3] * 1;
	out->z = (-1) * (mtrx->m[2][0] * in->x + mtrx->m[2][1] * in->y +
		mtrx->m[2][2] * in->z + mtrx->m[2][3] * 1);
}

void	mtrx4_x_vctr(t_vctr *out, t_mtrx4x4 *mtrx, t_vxyz *in)
{
	t_point		tail;
	t_point		new_tail;
	t_point		head;
	t_point		new_head;

	p_make(&tail, 0, 0, 0);
	p_make(&head, tail.x + in->x, tail.y + in->y, tail.z + in->z);
	mtrx4_x_point(&new_tail, mtrx, &tail);
	mtrx4_x_point(&new_head, mtrx, &head);
	v_make(out, &new_tail, &new_head);
}
