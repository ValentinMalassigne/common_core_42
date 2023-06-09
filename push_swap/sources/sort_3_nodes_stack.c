/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_nodes_stack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:12:37 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 14:17:52 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3_node_stack(t_list **stack)
{
	if (list_min(*stack) == *(int *)(*stack)->content)
	{
		ft_rra(stack);
		ft_sa(*stack);
	}
	else if (list_max(*stack) == *(int *)(*stack)->content)
	{
		ft_ra(stack);
		if (!is_ascending(*stack))
			ft_sa(*stack);
	}
	else
	{
		if (find_value_index(*stack, list_max(*stack)) == 1)
			ft_rra(stack);
		else
			ft_sa(*stack);
	}
}
