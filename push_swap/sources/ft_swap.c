/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:29:44 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/15 11:28:14 by vmalassi         ###   ########.fr       */
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

void	ft_sa(t_list *stack, int silent)
{
	ft_swap_stack_head(stack);
	if (silent == 0)
		ft_putstr_fd("sa\n", 1);
}

void	ft_sb(t_list *stack, int silent)
{
	ft_swap_stack_head(stack);
	if (silent == 0)
		ft_putstr_fd("sb\n", 1);
}

void	ft_ss(t_list *stack_a, t_list *stack_b, int silent)
{
	ft_swap_stack_head(stack_a);
	ft_swap_stack_head(stack_b);
	if (silent == 0)
		ft_putstr_fd("ss\n", 1);
}
