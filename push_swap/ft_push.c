/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 08:23:36 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/31 10:54:22 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_push_1_to_2(t_list **stack1, t_list **stack2)
{
	t_list	*temp;

	if (*stack1 == NULL)
		return ;
	temp = *stack1;
	*stack1 = temp->next;
	temp->next = *stack2;
	*stack2 = temp;
}

void	ft_pa(t_list **stack_a, t_list **stack_b)
{
	ft_push_1_to_2(stack_b, stack_a);
	ft_putstr_fd("pa", 1);
}

void	ft_pb(t_list **stack_a, t_list **stack_b)
{
	ft_push_1_to_2(stack_a, stack_b);
	ft_putstr_fd("pb", 1);
}
