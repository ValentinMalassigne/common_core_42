/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:20:29 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/20 17:14:01 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	parse_inputs(int argc, char **argv, t_infos *infos, t_philo *philo)
{
	if (argc == 5 || argc == 6)
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
	else
		printf("TODO, wrong number of inputs\n");
	return (0);
}

//TODO finir parsing
//securiser les inputs qui peuvent etre nimporte quoi

int	main(int argc, char **argv)
{
	t_infos infos;
	t_philo philo;
	if (!parse_inputs(argc, argv, &infos, &philo))
		return (0);
	printf("nb of philo %d\n",infos.number_of_philosophers);
	printf("time to die %d\n",philo.time_to_die);
	printf("time to eat %d\n",philo.time_to_eat);
	printf("time to sleep %d\n",philo.time_to_sleep);
	printf("max eat %d\n",infos.max_eat);
	return(0);
}
