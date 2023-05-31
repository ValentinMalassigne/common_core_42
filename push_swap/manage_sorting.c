/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:41:36 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/31 11:12:01 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*init_list(int argc, char **argv);
void			ft_free_content(void *content);

t_list	*manage_sorting(int argc, char **argv)
{
	t_list	*list_a;

	list_a = init_list(argc, argv);
	if (!list_a)
		return (NULL);
	//sort it
	return (list_a);
}

static int	*init_content(char *str)
{
	int	*value;

	value = malloc(sizeof(int));
	if (!value)
		return (NULL);
	*value = ft_atoi(str);
	return (value);
}

static t_list	*init_list(int argc, char **argv)
{
	t_list	*res;
	t_list	*new_node;
	int		i;
	int		*value;

	i = 1;
	res = NULL;
	while (i < argc)
	{
		value = init_content(argv[i]);
		if (!value)
		{
			ft_lstclear(&res, free);
			return (NULL);
		}
		new_node = ft_lstnew(value);
		if (!new_node)
		{
			ft_lstclear(&res, free);
			return (NULL);
		}
		ft_lstadd_back(&res, new_node);
		i++;
	}
	return (res);
}
