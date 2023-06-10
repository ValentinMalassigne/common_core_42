/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:41:36 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 16:23:19 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

static int	*init_content(char *str)
{
	int	*value;

	value = malloc(sizeof(int));
	if (!value)
		return (NULL);
	*value = ft_atoi(str);
	return (value);
}

static t_list	*init_list(int argc, char **argv, int start_index)
{
	t_list	*res;
	t_list	*new_node;
	int		i;
	int		*value;

	i = start_index;
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

static void	free_double_array(int length, char **array)
{
	while (length-- > 0)
		free(array[length]);
	free(array);
}

t_list	*manage_quote_input(char **argv)
{
	t_list	*res;
	char	**splited;
	int		arg_count;

	arg_count = 0;
	splited = ft_split(argv[1], ' ');
	while (splited[arg_count])
		arg_count++;
	if (!input_is_correct(arg_count, splited, 0))
	{
		free_double_array(arg_count, splited);
		return (NULL);
	}
	res = init_list(arg_count, splited, 0);
	free_double_array(arg_count, splited);
	return (res);
}

t_list	*manage_init(int argc, char **argv)
{
	t_list	*list_a;

	if (argc == 2)
	{
		return (manage_quote_input(argv));
	}
	else
	{
		if (!input_is_correct(argc, argv, 1))
			return (NULL);
		list_a = init_list(argc, argv, 1);
	}
	return (list_a);
}
