/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lowest_rotations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:58:50 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	get_lowest_rotations_from_a_to_b(t_list *stack_a, t_list *stack_b)
{
	int		i;
	t_list	*temp;

	temp = stack_a;
	i = count_rrarrb(stack_a, stack_b, *(int *) stack_a->content);
	while (temp)
	{
		if (i > count_rarb(stack_a, stack_b, *(int *)temp->content))
			i = count_rarb(stack_a, stack_b, *(int *)temp->content);
		if (i > count_rrarrb(stack_a, stack_b, *(int *)temp->content))
			i = count_rrarrb(stack_a, stack_b, *(int *)temp->content);
		if (i > count_rarrb(stack_a, stack_b, *(int *)temp->content))
			i = count_rarrb(stack_a, stack_b, *(int *)temp->content);
		if (i > count_rrarb(stack_a, stack_b, *(int *)temp->content))
			i = count_rrarb(stack_a, stack_b, *(int *)temp->content);
		temp = temp->next;
	}
	return (i);
}

int	get_lowest_rotations_from_b_to_a(t_list *stack_a, t_list *stack_b)
{
	int		i;
	t_list	*temp;

	temp = stack_b;
	i = count_rrarrb_a(stack_a, stack_b, *(int *) stack_b->content);
	while (temp)
	{
		if (i > count_rarb_a(stack_a, stack_b, *(int *)temp->content))
			i = count_rarb_a(stack_a, stack_b, *(int *)temp->content);
		if (i > count_rrarrb_a(stack_a, stack_b, *(int *)temp->content))
			i = count_rrarrb_a(stack_a, stack_b, *(int *)temp->content);
		if (i > count_rarrb_a(stack_a, stack_b, *(int *)temp->content))
			i = count_rarrb_a(stack_a, stack_b, *(int *)temp->content);
		if (i > count_rrarb_a(stack_a, stack_b, *(int *)temp->content))
			i = count_rrarb_a(stack_a, stack_b, *(int *)temp->content);
		temp = temp->next;
	}
	return (i);
}
