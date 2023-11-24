/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:13:03 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/24 20:33:54 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*philo_routine(void *params)
{
	t_philo	*philo = (t_philo *) params;
	t_philo	*right_thparams = philo->next;

	while (philo->meal_count < philo->infos.max_eat)
	{
		if (philo->number % 2 == 1)
		{
			pthread_mutex_lock(philo->mutex);
			printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
			pthread_mutex_lock(right_thparams->mutex);
			printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
		}
		else
		{
			pthread_mutex_lock(right_thparams->mutex);
			printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
			pthread_mutex_lock(philo->mutex);
			printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);			
		}
		philo->last_meal = get_ms_since_epoch();
		printf("%ld %d is eating\n", get_ms_since_epoch(), philo->number);
		usleep(philo->infos.time_to_eat * 1000);
		philo->meal_count++;
		pthread_mutex_unlock(philo->mutex);
		pthread_mutex_unlock(right_thparams->mutex);
		printf("%ld %d is sleeping\n", get_ms_since_epoch(), philo->number);
		usleep(philo->infos.time_to_sleep * 1000);
		printf("%ld %d is thinking\n", get_ms_since_epoch(), philo->number);
	}
	return NULL;
}

// int	any_philo_dead(t_philo *head)
// {
// 	int	start_philo;

// 	start_philo = head->number;
// 	head = head->next;
// 	while (head->number != start_philo)
// 	{
// 		if (get_ms_since_epoch() - head->last_meal > head->infos.time_to_die)
// 			return (1);
// 		head = head->next;
// 	}
// 	return (0);
// }

int	end_of_philo(t_philo *head, int philo_count)
{
	int	finished_eating_count;
	int	i;
	usleep(head->infos.time_to_die);
	while (1)
	{
		finished_eating_count = 0;
		i = 1;
		while(i <= philo_count)
		{
			if (head->infos.max_eat && head->meal_count >= head->infos.max_eat)
				finished_eating_count++;
			if (get_ms_since_epoch() - head->last_meal > head->infos.time_to_die)
			{
				printf("%ld %d died\n", get_ms_since_epoch(), head->number);
				return (1);
			}
			head = head->next;
			i++;
		}
		if (finished_eating_count == philo_count)
			return (1);
		usleep(10000);
	}
}