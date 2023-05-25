/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:36:24 by vmalassi          #+#    #+#             */
/*   Updated: 2023/04/18 09:23:44 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current->next;
		ft_lstdelone(current, del);
		current = temp;
	}
	*lst = NULL;
}
