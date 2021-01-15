/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:54:57 by rburton           #+#    #+#             */
/*   Updated: 2021/01/12 20:33:40 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	make_scn_arr(t_list **head, int size)
{
	int		i;
	char	**scn_arr;
	t_list	*tmp;

	scn_arr = ft_calloc(size + 1, sizeof(char *));
	tmp = *head;
	i = -1;
	while (tmp)
	{
		scn_arr[++i] = tmp->content;
		tmp = tmp->next;
	}
	strct_node(scn_arr, size);
}

//int		main(int argc, char **argv)
int		main(void)
{
	int		fd;
	char	*line;
	t_list	*head;

	//fd = open(argv[1], O_RDONLY);
	fd = open("/Users/rburton/minirt/scene.rt", O_RDONLY);

	line = NULL;
	head = NULL;
	
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));

	make_scn_arr(&head, ft_lstsize(head));
	close(fd);

	return (0);
}