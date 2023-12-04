/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:13:03 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/04 14:18:10 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	simu_finished(t_philo *philo)
{
	pthread_mutex_lock(philo->infos.lock_print);
	if (!*(philo->infos.philo_running))
	{
		pthread_mutex_unlock(philo->infos.lock_print);
		return (1);
	}
	pthread_mutex_unlock(philo->infos.lock_print);
	return (0);
}

void	safe_sleep(t_philo *philo, int ms_to_sleep)
{
	if (ms_to_sleep < 1000)
		usleep(1000 * ms_to_sleep);
	else
	{
		while (ms_to_sleep > 0)
		{
			usleep(1000);
			if (simu_finished(philo))
				return ;
			ms_to_sleep -= 1;
		}
	}
	return ;
}

static int	take_forks(t_philo *philo, t_philo *right_philo)
{
	if (simu_finished(philo))
		return (0);
	pthread_mutex_lock(philo->fork);
	if (simu_finished(philo))
	{
		pthread_mutex_unlock(philo->fork);
		return (0);
	}
	print_message(*philo, "has taken a fork");
	if (philo->number == right_philo->number)
		safe_sleep(philo, philo->infos.time_to_die);
	if (simu_finished(philo))
	{
		pthread_mutex_unlock(philo->fork);
		return (0);
	}
	pthread_mutex_lock(right_philo->fork);
	if (simu_finished(philo))
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(right_philo->fork);
		return (0);
	}
	print_message(*philo, "has taken a fork");
	return (1);
}

static void	manage_eat(t_philo *philo, t_philo *right_philo)
{
	pthread_mutex_lock(philo->infos.checking_death);
	philo->last_meal = get_ms_since_epoch();
	print_message(*philo, "is eating");
	philo->meal_count++;
	pthread_mutex_unlock(philo->infos.checking_death);
	safe_sleep(philo, philo->infos.time_to_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(right_philo->fork);
}

void	*philo_routine(void *params)
{
	t_philo	*philo;
	t_philo	*right_philo;

	philo = (t_philo *) params;
	right_philo = philo->next;
	while (!simu_finished(philo))
	{
		if (philo->infos.max_eat > 0 && philo->meal_count
			>= philo->infos.max_eat)
			return (NULL);
		if (philo->number % 2)
			usleep(5000);
		if (!take_forks(philo, right_philo))
			return (NULL);
		manage_eat(philo, right_philo);
		if (simu_finished(philo))
			return (NULL);
		print_message(*philo, "is sleeping");
		safe_sleep(philo, philo->infos.time_to_sleep);
		if (simu_finished(philo))
			return (NULL);
		print_message(*philo, "is thinking");
	}
	return (NULL);
}
