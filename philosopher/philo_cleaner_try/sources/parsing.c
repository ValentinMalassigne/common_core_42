/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:11:42 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/25 15:49:41 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	verify_inputs(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if(!ft_is_numeric(argv[1]) || !ft_is_numeric(argv[2])
			|| !ft_is_numeric(argv[3]) || !ft_is_numeric(argv[4])
			|| (argc == 6 && !ft_is_numeric(argv[5])))
		{
			printf("TODO, wrong input format\n");
			return (0);
		}
	}
	else
	{
		printf("TODO, wrong number of inputs\n");
		return (0);
	}
	return (1);
}

int	parse_inputs(int argc, char **argv, t_infos *infos, int *philo_count)
{
	if (verify_inputs(argc, argv))
	{
		*philo_count = ft_atoi(argv[1]);
		infos->time_to_die = ft_atoi(argv[2]);
		infos->time_to_eat = ft_atoi(argv[3]);
		infos->time_to_sleep = ft_atoi(argv[4]);
		infos->philo_running = NULL;
		if (argc == 6)
			infos->max_eat = ft_atoi(argv[5]);
		else
			infos->max_eat = -1;
		return (1);
	}
	return (0);
}