/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value_place.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:10:54 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	find_value_index(t_list *stack, int value)
{
	int	index;

	index = 0;
	while (*(int *) stack->content != value)
	{
		index++;
		stack = stack->next;
	}
	return (index);
}

int	find_value_place_in_b(t_list *stack_b, int value)
{
	int		i;
	t_list	*temp;

	i = 1;
	if (value > *(int *)stack_b->content
		&& value < *(int *)ft_lstlast(stack_b)->content)
		i = 0;
	else if (value > list_max(stack_b) || value < list_min(stack_b))
		i = find_value_index(stack_b, list_max(stack_b));
	else
	{
		temp = stack_b->next;
		while (*(int *)stack_b->content < value
			|| *(int *)temp->content > value)
		{
			stack_b = stack_b->next;
			temp = stack_b->next;
			i++;
		}
	}
	return (i);
}

int	find_value_place_in_a(t_list *stack_a, int value)
{
	int		i;
	t_list	*temp;

	i = 1;
	if (value < *(int *)stack_a->content
		&& value > *(int *)ft_lstlast(stack_a)->content)
		i = 0;
	else if (value > list_max(stack_a) || value < list_min(stack_a))
		i = find_value_index(stack_a, list_min(stack_a));
	else
	{
		temp = stack_a->next;
		while (*(int *)stack_a->content > value
			|| *(int *)temp->content < value)
		{
			stack_a = stack_a->next;
			temp = stack_a->next;
			i++;
		}
	}
	return (i);
}
