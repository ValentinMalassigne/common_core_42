/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:56:10 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/16 11:04:08 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

void	unknow_command_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	apply_output(t_list	**stack_a, t_list **stack_b, char *str)
{
	if (str[0] == 's' && str[1] == 'a' && str[2] == '\n')
		ft_sa(*stack_a, 1);
	else if (str[0] == 's' && str[1] == 'b' && str[2] == '\n')
		ft_sb(*stack_b, 1);
	else if (str[0] == 's' && str[1] == 's' && str[2] == '\n')
		ft_ss(*stack_a, *stack_b, 1);
	else if (str[0] == 'p' && str[1] == 'a' && str[2] == '\n')
		ft_pa(stack_a, stack_b, 1);
	else if (str[0] == 'p' && str[1] == 'b' && str[2] == '\n')
		ft_pb(stack_a, stack_b, 1);
	else if (str[0] == 'r' && str[1] == 'a' && str[2] == '\n')
		ft_ra(stack_a, 1);
	else if (str[0] == 'r' && str[1] == 'b' && str[2] == '\n')
		ft_rb(stack_b, 1);
	else if (str[0] == 'r' && str[1] == 'r' && str[2] == '\n')
		ft_rr(stack_a, stack_b, 1);
	else if (str[0] == 'r' && str[1] == 'r' && str[2] == 'a' && str[3] == '\n')
		ft_rra(stack_a, 1);
	else if (str[0] == 'r' && str[1] == 'r' && str[2] == 'b' && str[3] == '\n')
		ft_rrb(stack_b, 1);
	else if (str[0] == 'r' && str[1] == 'r' && str[2] == 'r' && str[3] == '\n')
		ft_rrr(stack_a, stack_b, 1);
	else
		unknow_command_error();
}

void	check_output(t_list *stack_a, char *last_output)
{
	t_list	*stack_b;

	stack_b = NULL;
	while (last_output && *last_output != '\n')
	{
		apply_output(&stack_a, &stack_b, last_output);
		free(last_output);
		last_output = get_next_line(0);
	}
	if (stack_b)
		ft_printf("KO\n");
	else if (!is_ascending(stack_a))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	free(last_output);
}

int	main(int argc, char **argv)
{
	t_list	*list;
	char	*push_swap_output;

	if (argc < 2)
		return (0);
	list = manage_init(argc, argv);
	if (!list)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	push_swap_output = get_next_line(0);
	if (!push_swap_output && !is_ascending(list))
		ft_printf("KO\n");
	else if (!push_swap_output && is_ascending(list))
		ft_printf("OK\n");
	else
		check_output(list, push_swap_output);
	ft_lstclear(&list, free);
	return (0);
}
