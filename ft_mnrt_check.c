/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 04:53:59 by rburton           #+#    #+#             */
/*   Updated: 2021/03/17 05:48:11 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"



void    check_node(char	**scn_arr, int size)
{
	int      i;
	int      j;
//    char     c;

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
	printf("first symbol: %c\n", scn_arr[1][j]);
}