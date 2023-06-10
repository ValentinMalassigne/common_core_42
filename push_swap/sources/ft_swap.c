/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:29:44 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

static void	ft_swap_stack_head(t_list *stack)
{
	void	*temp;

	if (!stack || stack->next == NULL)
		return ;
	temp = stack->content;
	stack->content = stack->next->content;
	stack->next->content = temp;
}

void	ft_sa(t_list *stack)
{
	ft_swap_stack_head(stack);
	ft_putstr_fd("sa\n", 1);
}

void	ft_sb(t_list *stack)
{
	ft_swap_stack_head(stack);
	ft_putstr_fd("sb\n", 1);
}

void	ft_ss(t_list *stack_a, t_list *stack_b)
{
	ft_swap_stack_head(stack_a);
	ft_swap_stack_head(stack_b);
	ft_putstr_fd("ss\n", 1);
}
