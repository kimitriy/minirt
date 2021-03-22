/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_prsr_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:05:46 by rburton           #+#    #+#             */
/*   Updated: 2021/03/22 13:37:33 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	set_rsltn(t_scn *nscn)
{
	t_set_rsltn t;

	if (nscn->save != '+')
		mlx_get_screen_size(nscn->vrs.mlx, (int*)&t.scr_w, (int*)&t.scr_h);
	else
	{
		t.scr_w = 16000;
		t.scr_h = 16000;
	}
	if (nscn->n_rsltn.x > t.scr_w || nscn->n_rsltn.y > t.scr_h)
	{
		t.ratio = (float)nscn->n_rsltn.x / (float)nscn->n_rsltn.y;
		t.orx = (float)nscn->n_rsltn.x / (float)t.scr_w;
		t.ory = (float)nscn->n_rsltn.y / (float)t.scr_h;
		if (t.orx >= t.ory)
		{
			nscn->n_rsltn.x = t.scr_w;
			nscn->n_rsltn.y = (int)t.scr_w / t.ratio;
		}
		else
		{
			nscn->n_rsltn.x = (int)t.scr_h * t.ratio;
			nscn->n_rsltn.y = t.scr_h;
		}
	}
}

void	write_rsltn(t_scn *nscn, t_prsr *np)
{
	check_values_node(np, 'r');
	nscn->n_rsltn.x = ft_atoi(np->rx);
	nscn->n_rsltn.y = ft_atoi(np->ry);
	set_rsltn(nscn);
}

void	write_ambnt(t_scn *nscn, t_prsr *np)
{
	check_values_node(np, 'a');
	nscn->n_ambnt.lvl = ft_atof(np->lvl);
	write_color(&nscn->n_ambnt.trgb, np);
}

void	write_cam(t_scn *nscn, t_prsr *np)
{
	t_cam	*tmp;

	check_values_node(np, 'o');
	tmp = NULL;
	make_t_cam(nscn);
	if (nscn->n_cntr.cam == 0)
		nscn->frst_cam = nscn->n_cam;
	if (nscn->n_cam->next != NULL)
		nscn->n_cam = nscn->n_cam->next;
	tmp = nscn->n_cam->content;
	write_p(&tmp->p, np);
	write_v(&tmp->v, np);
	tmp->fov = ft_atoi(np->fov);
	nscn->n_cntr.cam++;
}

void	write_lght(t_scn *nscn, t_prsr *np)
{
	t_lght *tmp;

	check_values_node(np, 'l');
	tmp = NULL;
	make_t_lght(nscn);
	if (nscn->n_cntr.lght == 0)
		nscn->frst_lght = nscn->n_lght;
	if (nscn->n_lght->next != NULL)
		nscn->n_lght = nscn->n_lght->next;
	tmp = nscn->n_lght->content;
	write_p(&tmp->p, np);
	tmp->lvl = ft_atof(np->lvl);
	write_color(&tmp->trgb, np);
	nscn->n_cntr.lght++;
}
