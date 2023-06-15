/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 08:23:36 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/15 11:28:14 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

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

void	ft_pa(t_list **stack_a, t_list **stack_b, int silent)
{
	ft_push_1_to_2(stack_b, stack_a);
	if (silent == 0)
		ft_putstr_fd("pa\n", 1);
}

void	ft_pb(t_list **stack_a, t_list **stack_b, int silent)
{
	ft_push_1_to_2(stack_a, stack_b);
	if (silent == 0)
		ft_putstr_fd("pb\n", 1);
}
