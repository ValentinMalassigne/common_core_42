/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:06:55 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/15 11:28:14 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

static void	ft_rotate_stack(t_list **stack)
{
	t_list	*temp;

	if (*stack == NULL)
		return ;
	temp = *stack;
	*stack = temp->next;
	temp->next = NULL;
	ft_lstadd_back(stack, temp);
}

void	ft_ra(t_list **stack, int silent)
{
	ft_rotate_stack(stack);
	if (silent == 0)
		ft_putstr_fd("ra\n", 1);
}

void	ft_rb(t_list **stack, int silent)
{
	ft_rotate_stack(stack);
	if (silent == 0)
		ft_putstr_fd("rb\n", 1);
}

void	ft_rr(t_list **stack_a, t_list **stack_b, int silent)
{
	ft_rotate_stack(stack_a);
	ft_rotate_stack(stack_b);
	if (silent == 0)
		ft_putstr_fd("rr\n", 1);
}
