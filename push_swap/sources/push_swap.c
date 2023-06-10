/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:18:38 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:55:49 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*list;

	if (argc < 2)
		return (0);
	list = manage_init(argc, argv);
	if (!list)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	if (!is_ascending(list))
		sort_any(&list);
	ft_lstclear(&list, free);
	return (0);
}

/*
#include <stdio.h>
void	ft_putlist(t_list *list)
{
	t_list	*current;
	int		*value;

	current = list;
	while (current != NULL)
	{
		value = current->content;
		printf("%d\n", *value);
		current = current->next;
	}
}*/
