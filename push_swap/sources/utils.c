/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:41:03 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	is_ascending(t_list *list)
{
	while (list->next)
	{
		if (*(int *)list->content > *(int *)list->next->content)
			return (0);
		list = list->next;
	}
	return (1);
}

int	list_min(t_list *stack_a)
{
	int	res;

	res = *(int *)stack_a->content;
	while (stack_a)
	{
		if (*(int *)stack_a->content < res)
			res = *(int *)stack_a->content;
		stack_a = stack_a->next;
	}
	return (res);
}

int	list_max(t_list *stack_a)
{
	int	res;

	res = *(int *)stack_a->content;
	while (stack_a)
	{
		if (*(int *)stack_a->content > res)
			res = *(int *)stack_a->content;
		stack_a = stack_a->next;
	}
	return (res);
}
