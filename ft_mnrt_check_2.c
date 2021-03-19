/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:14:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/19 09:31:26 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	n_arg(char *l, int n)
{
	int		i;
	int		arg_cntr;
	int		nxt;

	i = -1;
	arg_cntr = 0;
	while (++i < (int)ft_strlen(l))
	{
		if (ft_isdigit(l[i]) == 1)
		{
			nxt = -1;
			while ((++nxt + i) < (int)ft_strlen(l))
			{
				if ((ft_isdigit(l[i + nxt]) == 0 && l[i + nxt] != '.')
					|| l[i + nxt + 1] == '\0')
				{
					arg_cntr++;
					i += nxt;
					break ;
				}
			}
		}
	}
	if (arg_cntr != n)
		err_message("Invalid number of arguments.");
}

void	check_args(char *l)
{
	if (l[0] == 'R')
		n_arg(l, 2);
	else if (l[0] == 'A')
		n_arg(l, 4);
	else if (l[0] == 'c' && l[1] != 'y')
		n_arg(l, 7);
	else if (l[0] == 'l')
		n_arg(l, 7);
	else if (l[0] == 's' && l[1] == 'p')
		n_arg(l, 7);
	else if (l[0] == 'p' && l[1] == 'l')
		n_arg(l, 9);
	else if (l[0] == 's' && l[1] == 'q')
		n_arg(l, 10);
	else if (l[0] == 'c' && l[1] == 'y')
		n_arg(l, 11);
	else if (l[0] == 't' && l[1] == 'r')
		n_arg(l, 12);
}

void	check_line(char *line, t_vldt *v)
{
	check_keys(line, v);
	check_delimeters(line);
	check_args(line);
}

void	check_node(char **scn_arr, int size)
{
	int		i;
	t_vldt	v;

	vldt_null(&v);
	rt_print(scn_arr, size);
	i = 0;
	while (i < size)
	{
		if (scn_arr[i][0] != '\0' && scn_arr[i][0] != '#')
			check_line(scn_arr[i], &v);
		i++;
	}
}
