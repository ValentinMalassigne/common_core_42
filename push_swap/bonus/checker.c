/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:56:10 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/10 14:26:17 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/checker.h"

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
	
	ft_lstclear(&list, free);
	return (0);
}
