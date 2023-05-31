/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:18:38 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/31 11:04:48 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putlist(t_list *list);

int	main(int argc, char **argv)
{
	t_list	*sorted_list;

	if (argc < 2)
		return (0);
	if (!input_is_correct(argc, argv))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	sorted_list = manage_sorting(argc, argv);
	if (!sorted_list)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	ft_putlist(sorted_list);
	ft_lstclear(&sorted_list, free);
	return (0);
}

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
}
