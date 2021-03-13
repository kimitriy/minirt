/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:54:57 by rburton           #+#    #+#             */
/*   Updated: 2021/03/13 14:29:35 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_argv(int argc, char **argv)
{
	int		i;

	if (argc > 3)
		err_message("Error. Wrong number of arguments.");
	if (argv[1] == NULL)
		err_message("Error. Scene file is not specified.");
	else
	{
		i = ft_strlen(argv[1]);
		if (ft_strcmp(&argv[1][i - 3], ".rt") != 0)
			err_message("Error. Wrong name of scene file.");
	}
}

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

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_list	*head;

	check_argv(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		err_message("Error. Scene file doesn't exist.");
	line = NULL;
	head = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	make_scn_arr(&head, ft_lstsize(head));
	close(fd);
	return (0);
}