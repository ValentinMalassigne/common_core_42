/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:20:29 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/21 15:41:35 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	verify_inputs(int argc, char **argv)
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

int	parse_inputs(int argc, char **argv, t_infos *infos, t_philo *philo)
{
	if (verify_inputs(argc, argv))
	{
		infos->number_of_philosophers = ft_atoi(argv[1]);
		philo->time_to_die = ft_atoi(argv[2]);
		philo->time_to_eat = ft_atoi(argv[3]);
		philo->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			infos->max_eat = ft_atoi(argv[5]);
		else
			infos->max_eat = -1;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_infos infos;
	t_philo philo;
	if (!parse_inputs(argc, argv, &infos, &philo))
		return (0);
	
	
	// printf("nb of philo %d\n",infos.number_of_philosophers);
	// printf("time to die %d\n",philo.time_to_die);
	// printf("time to eat %d\n",philo.time_to_eat);
	// printf("time to sleep %d\n",philo.time_to_sleep);
	// printf("max eat %d\n",infos.max_eat);
	return(0);
}
