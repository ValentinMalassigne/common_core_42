/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:18:38 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/16 08:23:58 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*list;

	if (argc < 2)
		return (0);
	list = manage_init(argc, argv);
	if (!list)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	if (!is_ascending(list))
		sort_any(&list);
	ft_lstclear(&list, free);
	return (0);
}
