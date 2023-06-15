/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:02:45 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/15 11:05:02 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

static void	reduce_a_to_size_3(t_list **stack_a, t_list **stack_b)
{
	int		i;
	t_list	*temp;
	int		*temp_value;

	while (ft_lstsize(*stack_a) > 3 && !is_ascending(*stack_a))
	{
		temp = *stack_a;
		i = get_lowest_rotations_from_a_to_b(*stack_a, *stack_b);
		while (i >= 0)
		{
			temp_value = temp->content;
			if (i == count_rarb(*stack_a, *stack_b, *temp_value))
				i = apply_rarb(stack_a, stack_b, *temp_value, 'a');
			else if (i == count_rrarrb(*stack_a, *stack_b, *temp_value))
				i = apply_rrarrb(stack_a, stack_b, *temp_value, 'a');
			else if (i == count_rarrb(*stack_a, *stack_b, *temp_value))
				i = apply_rarrb(stack_a, stack_b, *temp_value, 'a');
			else if (i == count_rrarb(*stack_a, *stack_b, *temp_value))
				i = apply_rrarb(stack_a, stack_b, *temp_value, 'a');
			else
				temp = temp->next;
		}
	}
}

static t_list	*sort_stack_b(t_list **stack_a)
{
	t_list	*stack_b;

	stack_b = NULL;
	if (ft_lstsize(*stack_a) > 3 && !is_ascending(*stack_a))
		ft_pb(stack_a, &stack_b, 0);
	if (ft_lstsize(*stack_a) > 3 && !is_ascending(*stack_a))
		ft_pb(stack_a, &stack_b, 0);
	if (ft_lstsize(*stack_a) > 3 && !is_ascending(*stack_a))
		reduce_a_to_size_3(stack_a, &stack_b);
	if (!is_ascending(*stack_a))
		sort_3_node_stack(stack_a);
	return (stack_b);
}

static t_list	**sort_stack_a(t_list **stack_a, t_list **stack_b)
{
	int		i;
	t_list	*temp;
	int		*temp_value;

	while (*stack_b)
	{
		temp = *stack_b;
		i = get_lowest_rotations_from_b_to_a(*stack_a, *stack_b);
		while (i >= 0)
		{
			temp_value = temp->content;
			if (i == count_rarb_a(*stack_a, *stack_b, *temp_value))
				i = apply_rarb(stack_a, stack_b, *temp_value, 'b');
			else if (i == count_rarrb_a(*stack_a, *stack_b, *temp_value))
				i = apply_rarrb(stack_a, stack_b, *temp_value, 'b');
			else if (i == count_rrarrb_a(*stack_a, *stack_b, *temp_value))
				i = apply_rrarrb(stack_a, stack_b, *temp_value, 'b');
			else if (i == count_rrarb_a(*stack_a, *stack_b, *temp_value))
				i = apply_rrarb(stack_a, stack_b, *temp_value, 'b');
			else
				temp = temp->next;
		}
	}
	return (stack_a);
}

void	sort_any(t_list **stack_a)
{
	t_list	*stack_b;
	int		i;

	stack_b = NULL;
	if (ft_lstsize(*stack_a) == 2)
		ft_sa(*stack_a, 0);
	else
	{
		stack_b = sort_stack_b(stack_a);
		stack_a = sort_stack_a(stack_a, &stack_b);
		i = find_value_index(*stack_a, list_min(*stack_a));
		if (i < ft_lstsize(*stack_a) - i)
		{
			while (*(int *)(*stack_a)->content != list_min(*stack_a))
				ft_ra(stack_a, 0);
		}
		else
		{
			while (*(int *)(*stack_a)->content != list_min(*stack_a))
				ft_rra(stack_a, 0);
		}
	}
}
