/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 04:53:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/18 11:41:41 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	rt_print(char **scn_arr, int size)
{
	int      i;
	int      j;

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
	// printf("first symbol: %c\n", scn_arr[1][j]);
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
		else if (l[0] != 's' && l[0] != 'p' && l[0] != 'c' && l[0] != 't' && l[1] != 9 && l[1] != 32) //!
			err_message("Invalid key.");
		else if ((l[1] == 'p' || l[1] == 'l' || l[1] == 'q' || l[1] == 'y' || l[1] == 'r') && l[2] != 9 && l[2] != 32)
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
	if (l[i] == ',' && ft_isdigit(l[i + 1]) == 0 && (l[i + 1] == 9 || (ft_isdigit(l[i + 2]) == 0 && l[i + 2] != '-')))
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
		if (ft_isalpha(l[i]) == 0 && ft_isdigit(l[i]) == 0 && l[i] != '.' && l[i] != ',' && l[i] != '-')
			if (l[i] != 9 && l[i] != 32)
				err_message("Invalid delimeter.");
		if (ft_isalpha(l[i]) == 0 && ft_isdigit(l[i]) == 0 && (l[i] == '.' || l[i] == ',' || l[i] == '-'))
			p_marks_hndlr(l, i);
	}
}

void	n_arg(char *l, int n)
{
	int		i;
	int		arg_cntr;
	int		nxt;

	i = 0;
	arg_cntr = 0;
	while (i < (int)ft_strlen(l))
	{
		if (ft_isdigit(l[i]) == 1)
		{
			nxt = 0;
			while ((i + nxt) < (int)ft_strlen(l))
			{
				if ((ft_isdigit(l[i + nxt]) == 0 && l[i + nxt] != '.') || l[i + nxt + 1] == '\0')
				{
					arg_cntr++;
					i += nxt;
					break ;
				}
				nxt++;
			}
		}
		i++;
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

void    check_node(char **scn_arr, int size)
{
	int      i;
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