/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:45:34 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/10 14:25:41 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../libft/headers/libft.h"

t_list	*manage_init(int argc, char **argv);
void	ft_sa(t_list *stack);
void	ft_sb(t_list *stack);
void	ft_ss(t_list *stack_a, t_list *stack_b);
void	ft_pa(t_list **stack_a, t_list **stack_b);
void	ft_pb(t_list **stack_a, t_list **stack_b);
void	ft_ra(t_list **stack);
void	ft_rb(t_list **stack);
void	ft_rr(t_list **stack_a, t_list **stack_b);
void	ft_rra(t_list **stack);
void	ft_rrb(t_list **stack);
void	ft_rrr(t_list **stack_a, t_list **stack_b);
void	sort_3_node_stack(t_list **stack);
void	sort_any(t_list **stack_a);
int		input_is_correct(int argc, char **argv, int start_index);
int		is_ascending(t_list *list);
int		list_min(t_list *stack_a);
int		list_max(t_list *stack_a);
int		find_value_place_in_b(t_list *stack_b, int value);
int		find_value_place_in_a(t_list *stack_a, int value);
int		count_rrarrb(t_list *stack_a, t_list *stack_b, int value);
int		find_value_index(t_list *stack, int value);
int		get_lowest_rotations_from_a_to_b(t_list *stack_a, t_list *stack_b);
int		get_lowest_rotations_from_b_to_a(t_list *stack_a, t_list *stack_b);
int		count_rrarrb(t_list *stack_a, t_list *stack_b, int value);
int		count_rarb(t_list *stack_a, t_list *stack_b, int value);
int		count_rrarb(t_list *stack_a, t_list *stack_b, int value);
int		count_rarrb(t_list *stack_a, t_list *stack_b, int value);
int		count_rarb_a(t_list *stack_a, t_list *stack_b, int value);
int		count_rrarrb_a(t_list *stack_a, t_list *stack_b, int value);
int		count_rarrb_a(t_list *stack_a, t_list *stack_b, int value);
int		count_rrarb_a(t_list *stack_a, t_list *stack_b, int value);
int		apply_rarb(t_list **stack_a, t_list **stack_b, int value, char c);
int		apply_rrarrb(t_list **stack_a, t_list **stack_b, int value, char c);
int		apply_rrarb(t_list **stack_a, t_list **stack_b, int value, char c);
int		apply_rarrb(t_list **stack_a, t_list **stack_b, int value, char c);

#endif