/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:47:20 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 14:20:13 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	apply_rarb(t_list **stack_a, t_list **stack_b, int value, char c)
{
	if (c == 'a')
	{
		while (*(int *)(*stack_a)->content != value
			&& find_value_place_in_b(*stack_b, value) > 0)
			ft_rr(stack_a, stack_b);
		while (*(int *)(*stack_a)->content != value)
			ft_ra(stack_a);
		while (find_value_place_in_b(*stack_b, value) > 0)
			ft_rb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while (*(int *)(*stack_b)->content != value
			&& find_value_place_in_a(*stack_a, value) > 0)
			ft_rr(stack_a, stack_b);
		while (*(int *)(*stack_b)->content != value)
			ft_rb(stack_b);
		while (find_value_place_in_a(*stack_a, value) > 0)
			ft_ra(stack_a);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}

int	apply_rrarrb(t_list **stack_a, t_list **stack_b, int value, char c)
{
	if (c == 'a')
	{
		while (*(int *)(*stack_a)->content != value
			&& find_value_place_in_b(*stack_b, value) > 0)
			ft_rrr(stack_a, stack_b);
		while (*(int *)(*stack_a)->content != value)
			ft_rra(stack_a);
		while (find_value_place_in_b(*stack_b, value) > 0)
			ft_rrb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while (*(int *)(*stack_b)->content != value
			&& find_value_place_in_a(*stack_a, value) > 0)
			ft_rrr(stack_a, stack_b);
		while (*(int *)(*stack_b)->content != value)
			ft_rrb(stack_b);
		while (find_value_place_in_a(*stack_a, value) > 0)
			ft_rra(stack_a);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}

int	apply_rrarb(t_list **stack_a, t_list **stack_b, int value, char c)
{
	if (c == 'a')
	{
		while (*(int *)(*stack_a)->content != value)
			ft_rra(stack_a);
		while (find_value_place_in_b(*stack_b, value) > 0)
			ft_rb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while (find_value_place_in_a(*stack_a, value) > 0)
			ft_rra(stack_a);
		while (*(int *)(*stack_b)->content != value)
			ft_rb(stack_b);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}

int	apply_rarrb(t_list **stack_a, t_list **stack_b, int value, char c)
{
	if (c == 'a')
	{
		while (*(int *)(*stack_a)->content != value)
			ft_ra(stack_a);
		while (find_value_place_in_b(*stack_b, value) > 0)
			ft_rrb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while (find_value_place_in_a(*stack_a, value) > 0)
			ft_ra(stack_a);
		while (*(int *)(*stack_b)->content != value)
			ft_rrb(stack_b);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}
