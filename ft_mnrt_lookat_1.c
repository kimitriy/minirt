/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lookat_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:11:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 20:22:42 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	null_lookat(t_look_at *lookat)
{
	if (lookat->tmp != '+')
		v_null(&lookat->v_tmp);
	v_null(&lookat->v_f);
	v_null(&lookat->v_r);
	v_null(&lookat->v_up);
}

void	v_tmp_make(t_vctr *vf, t_vctr *vtmp, t_look_at *lkt)
{
	if (lkt->tmp != '+')
	{
		vtmp->xyz.x = 0;
		if (vf->nxyz.y == 1)
		{
			vtmp->xyz.y = 0;
			vtmp->xyz.z = -1;
		}
		else if (vf->xyz.y == -1)
		{
			vtmp->xyz.y = 0;
			vtmp->xyz.z = 1;
		}
		else
		{
			vtmp->xyz.y = 1;
			vtmp->xyz.z = 0;
		}
	}
	v_fill(vtmp);
}

void	look_at_mtrx(t_look_at *lookat, t_vctr *vf, t_point *p)
{
	null_lookat(lookat);
	v_n_prdct(&lookat->v_f.xyz, &vf->nxyz, -1);
	v_fill(&lookat->v_f);
	v_tmp_make(&lookat->v_f, &lookat->v_tmp, lookat);
	v_crss_prdct(&lookat->v_r.xyz, &lookat->v_f.nxyz, &lookat->v_tmp.nxyz);
	v_fill(&lookat->v_r);
	v_crss_prdct(&lookat->v_up.xyz, &lookat->v_r.nxyz, &lookat->v_f.nxyz);
	v_fill(&lookat->v_up);
	lookat->m.m[0][0] = lookat->v_r.nxyz.x;
	lookat->m.m[0][1] = lookat->v_r.nxyz.y;
	lookat->m.m[0][2] = lookat->v_r.nxyz.z;
	lookat->m.m[0][3] = -v_x_point_prdct(&lookat->v_r.nxyz, p);
	lookat->m.m[1][0] = lookat->v_up.nxyz.x;
	lookat->m.m[1][1] = lookat->v_up.nxyz.y;
	lookat->m.m[1][2] = lookat->v_up.nxyz.z;
	lookat->m.m[1][3] = -v_x_point_prdct(&lookat->v_up.nxyz, p);
	lookat->m.m[2][0] = lookat->v_f.nxyz.x;
	lookat->m.m[2][1] = lookat->v_f.nxyz.y;
	lookat->m.m[2][2] = lookat->v_f.nxyz.z;
	lookat->m.m[2][3] = -v_x_point_prdct(&lookat->v_f.nxyz, p);
	lookat->m.m[3][0] = 0;
	lookat->m.m[3][1] = 0;
	lookat->m.m[3][2] = 0;
	lookat->m.m[3][3] = 1;
}

void	get_cam_fov(t_scn *nscn, t_scn *lscn)
{
	t_cam	*cam;
	t_cam	*lcam;

	make_t_cam(lscn);
	if (lscn->n_cntr.cam == 0)
		lscn->frst_cam = lscn->n_cam;
	if (lscn->n_cam->next != NULL)
		lscn->n_cam = lscn->n_cam->next;
	cam = nscn->n_cam->content;
	lcam = lscn->n_cam->content;
	lcam->fov = cam->fov;
	lscn->n_cntr.cam++;
}
