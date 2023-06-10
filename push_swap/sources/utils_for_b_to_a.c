/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_b_to_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:23:57 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	count_rarb_a(t_list *stack_a, t_list *stack_b, int value)
{
	int	i;

	i = find_value_place_in_a(stack_a, value);
	if (i < find_value_index(stack_b, value))
		i = find_value_index(stack_b, value);
	return (i);
}

int	count_rrarrb_a(t_list *stack_a, t_list *stack_b, int value)
{
	int	i;

	i = 0;
	if (find_value_place_in_a(stack_a, value))
		i = ft_lstsize(stack_a) - find_value_place_in_a(stack_a, value);
	if ((i < (ft_lstsize(stack_b) - find_value_index(stack_b, value)))
		&& find_value_index(stack_b, value))
		i = ft_lstsize(stack_b) - find_value_index(stack_b, value);
	return (i);
}

int	count_rarrb_a(t_list *stack_a, t_list *stack_b, int value)
{
	int	i;

	i = 0;
	if (find_value_index(stack_b, value))
		i = ft_lstsize(stack_b) - find_value_index(stack_b, value);
	i = find_value_place_in_a(stack_a, value) + i;
	return (i);
}

int	count_rrarb_a(t_list *stack_a, t_list *stack_b, int value)
{
	int	i;

	i = 0;
	if (find_value_place_in_a(stack_a, value))
		i = ft_lstsize(stack_a) - find_value_place_in_a(stack_a, value);
	i = find_value_index(stack_b, value) + i;
	return (i);
}
