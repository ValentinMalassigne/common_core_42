/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:45:34 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/31 10:39:28 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

//includes to remove :
# include <stdio.h>

/*les solutions :
	la t_list : pb il faut lui donner des pointeurs comme content
	faire une structure avec un tableau d'int et une size
	faire une structure avec data et next et une structure avec size et head
*/

t_list	*manage_sorting(int argc, char **argv);
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
int		input_is_correct(int argc, char **argv);

#endif