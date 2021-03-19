/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_strct_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:51:13 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 18:03:10 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	make_t_rsltn(t_scn *scn)
{
	scn->n_rsltn.x = 0;
	scn->n_rsltn.y = 0;
}

void	make_t_ambnt(t_scn *scn)
{
	scn->n_ambnt.lvl = 0;
	color_make(&scn->n_ambnt.trgb, 0, 0, 0);
}

void	make_t_cam(t_scn *scn)
{
	t_cam	*new_cam;

	if (!(new_cam = (t_cam*)malloc(1 * sizeof(t_cam))))
		new_cam = NULL;
	p_make(&new_cam->p, 0, 0, 0);
	v_null(&new_cam->v);
	new_cam->fov = 0;
	new_cam->nxt = NULL;
	ft_lstadd_back(&scn->n_cam, ft_lstnew(new_cam));
}

void	t_lght_null(t_lght *lght)
{
	p_make(&lght->p, 0, 0, 0);
	lght->lvl = 0;
	color_make(&lght->trgb, 0, 0, 0);
	lght->nxt = NULL;
}

void	make_t_lght(t_scn *scn)
{
	t_lght	*new_lght;

	if (!(new_lght = (t_lght*)malloc(1 * sizeof(t_lght))))
		new_lght = NULL;
	t_lght_null(new_lght);
	ft_lstadd_back(&scn->n_lght, ft_lstnew(new_lght));
}
