/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:13:03 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/30 09:54:41 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	take_fork(t_philo *philo)
{
	if (!*(philo->infos.philo_running))
		return (0);
	pthread_mutex_lock(philo->mutex);
	if (!*(philo->infos.philo_running))
	{
		pthread_mutex_unlock(philo->mutex);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	t_philo	*right_thparams = philo->next;
	if (philo->number % 2 == 1)
	{
		if (!take_fork(philo))
			return (0);
		printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
		if (!take_fork(right_thparams))
			return (0);
		printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
	}
	else
	{
		if (!take_fork(right_thparams))
			return (0);
		printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
		if (!take_fork(philo))
			return (0);
		printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
	}
	return (1);
}

int eating(t_philo *philo)
{
	t_philo	*right_thparams = philo->next;

	philo->last_meal = get_ms_since_epoch();
	if (!*(philo->infos.philo_running))
	{
		pthread_mutex_unlock(philo->mutex);
		pthread_mutex_unlock(right_thparams->mutex);
		return (0);
	}
	printf("%ld %d is eating\n", get_ms_since_epoch(), philo->number);
	usleep(philo->infos.time_to_eat * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_unlock(right_thparams->mutex);
	return (1);
}

int	chilling(t_philo *philo)
{
	if (!*(philo->infos.philo_running))
		return (0);
	printf("%ld %d is sleeping\n", get_ms_since_epoch(), philo->number);
	usleep(philo->infos.time_to_sleep * 1000);
	if (!*(philo->infos.philo_running))
		return (0);
	printf("%ld %d is thinking\n", get_ms_since_epoch(), philo->number);
	return (1);
}

void	*philo_routine(void *params)
{
	t_philo	*philo = (t_philo *) params;

	while (*(philo->infos.philo_running))
	{
		if (philo->infos.max_eat > 0 && philo->meal_count >= philo->infos.max_eat)
			return (NULL);
		if (!take_forks(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!chilling(philo))
			return (NULL);
	}
	return (NULL);
}

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
			if (head->infos.max_eat > 0 && head->meal_count >= head->infos.max_eat)
				finished_eating_count++;
			if (get_ms_since_epoch() - head->last_meal > head->infos.time_to_die)
			{
				printf("%ld %d died\n", get_ms_since_epoch(), head->number);
				return (0);
			}
			head = head->next;
			i++;
		}
		if (finished_eating_count == philo_count)
			return (0);
		usleep(10000);
	}
}
