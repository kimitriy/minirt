/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 04:53:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 09:21:02 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	rt_print(char **scn_arr, int size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (scn_arr[i][j])
		{
			printf("%c", scn_arr[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
}

void	vldt_null(t_vldt *v)
{
	v->a_cnt = 0;
	v->r_cnt = 0;
}

void	check_keys(char *l, t_vldt *v)
{
	const char	fs[] = "#RAclspt";

	if ((l[0] && ft_strchr(fs, l[0]) != NULL))
	{
		if (l[0] == 'c' && l[1] != 'y' && l[1] != 32 && l[1] != 9)
			err_message("Invalid key.");
		else if (l[0] == 's' && l[1] != 'p' && l[1] != 'q')
			err_message("Invalid key.");
		else if ((l[0] == 'p' && l[1] != 'l') || (l[0] == 't' && l[1] != 'r'))
			err_message("Invalid key.");
		else if (l[0] != 's' && l[0] != 'p' && l[0] != 'c'
			&& l[0] != 't' && l[1] != 9 && l[1] != 32)
			err_message("Invalid key.");
		else if ((l[1] == 'p' || l[1] == 'l' || l[1] == 'q' ||
			l[1] == 'y' || l[1] == 'r') && l[2] != 9 && l[2] != 32)
			err_message("Invalid key.");
		if (l[0] == 'R')
			v->r_cnt++;
		else if (l[0] == 'A')
			v->a_cnt++;
		if (v->r_cnt == 0 || v->r_cnt > 1 || v->a_cnt > 1)
			err_message("Invalid key.");
	}
	else if (l[0] && ft_strchr(fs, l[0]) == NULL)
		err_message("Invalid key.");
}

void	p_marks_hndlr(char *l, int i)
{
	if ((l[i] == '.' || l[i] == ',') && ft_isdigit(l[i - 1]) == 0)
		err_message("Invalid delimeter.");
	if ((l[i] == '.' || l[i] == '-') && ft_isdigit(l[i + 1]) == 0)
		err_message("Invalid delimeter.");
	if (l[i] == ',' && ft_isdigit(l[i + 1]) == 0 && (l[i + 1] == 9
		|| (ft_isdigit(l[i + 2]) == 0 && l[i + 2] != '-')))
		err_message("Invalid delimeter.");
	if (l[i] == ',' && ft_isdigit(l[i - 1]) == 0 && ft_isdigit(l[i + 1]) == 0)
		err_message("Invalid delimeter.");
}

void	check_delimeters(char *l)
{
	int		i;
	char	no_dgts;

	no_dgts = '\0';
	i = -1;
	while (++i < (int)ft_strlen(l))
	{
		if (ft_isalpha(l[i]) == 0 && no_dgts == '\0')
			no_dgts = '+';
		if (ft_isalpha(l[i]) == 1 && no_dgts == '+')
			err_message("Invalid delimeter.");
		if (ft_isalpha(l[i]) == 0 && ft_isdigit(l[i]) == 0 &&
			l[i] != '.' && l[i] != ',' && l[i] != '-')
			if (l[i] != 9 && l[i] != 32)
				err_message("Invalid delimeter.");
		if (ft_isalpha(l[i]) == 0 && ft_isdigit(l[i]) == 0 &&
			(l[i] == '.' || l[i] == ',' || l[i] == '-'))
			p_marks_hndlr(l, i);
	}
}
