/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_nodes_stack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:12:37 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/16 10:49:27 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

void	sort_3_node_stack(t_list **stack)
{
	if (list_min(*stack) == *(int *)(*stack)->content)
	{
		ft_rra(stack, 0);
		ft_sa(*stack, 0);
	}
	else if (list_max(*stack) == *(int *)(*stack)->content)
	{
		ft_ra(stack, 0);
		if (!is_ascending(*stack))
			ft_sa(*stack, 0);
	}
	else
	{
		if (find_value_index(*stack, list_max(*stack)) == 1)
			ft_rra(stack, 0);
		else
			ft_sa(*stack, 0);
	}
}
