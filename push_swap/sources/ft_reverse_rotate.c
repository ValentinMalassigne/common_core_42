/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:31:06 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

static void	remove_last_node(t_list **stack)
{
	t_list	*current;

	current = *stack;
	while (current->next->next != NULL)
		current = current->next;
	current->next = NULL;
}

static void	ft_reverse_rotate_stack(t_list **stack)
{
	t_list	*temp;

	if (*stack == NULL)
		return ;
	temp = ft_lstlast(*stack);
	remove_last_node(stack);
	ft_lstadd_front(stack, temp);
}

void	ft_rra(t_list **stack)
{
	ft_reverse_rotate_stack(stack);
	ft_putstr_fd("rra\n", 1);
}

void	ft_rrb(t_list **stack)
{
	ft_reverse_rotate_stack(stack);
	ft_putstr_fd("rrb\n", 1);
}

void	ft_rrr(t_list **stack_a, t_list **stack_b)
{
	ft_reverse_rotate_stack(stack_a);
	ft_reverse_rotate_stack(stack_b);
	ft_putstr_fd("rr\n", 1);
}
