/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:13:03 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/02 12:01:33 by vmalassi         ###   ########.fr       */
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

void	*philo_routine(void *params)
{
	t_philo	*philo = (t_philo *) params;
	t_philo	*right_philo = philo->next;

	while (!simu_finished(philo))
	{
		if (philo->infos.max_eat > 0 && philo->meal_count >= philo->infos.max_eat)
			return NULL;
		// if (philo->number % 2)
		// usleep(15000);
		if (philo->number % 2 == 1)
		{
			if (simu_finished(philo))
				return NULL;
			pthread_mutex_lock(philo->fork);
			if (simu_finished(philo))
			{
				pthread_mutex_unlock(philo->fork);
				return NULL;
			}
			print_message(*philo, "has taken a fork");
			if (simu_finished(philo))
			{
				pthread_mutex_unlock(philo->fork);
				return NULL;
			}
			pthread_mutex_lock(right_philo->fork);
			if (simu_finished(philo))
			{
				pthread_mutex_unlock(philo->fork);
				pthread_mutex_unlock(right_philo->fork);
				return NULL;
			}
			print_message(*philo, "has taken a fork");
		}
		else
		{
			if (simu_finished(philo))
				return NULL;
			pthread_mutex_lock(right_philo->fork);
			if (simu_finished(philo))
			{
				pthread_mutex_unlock(right_philo->fork);
				return NULL;
			}
			print_message(*philo, "has taken a fork");
			if (simu_finished(philo))
			{
				pthread_mutex_unlock(right_philo->fork);
				return NULL;
			}
			pthread_mutex_lock(philo->fork);
			if (simu_finished(philo))
			{
				pthread_mutex_unlock(philo->fork);
				pthread_mutex_unlock(right_philo->fork);
				return NULL;
			}
			print_message(*philo, "has taken a fork");			
		}
		pthread_mutex_lock(philo->infos.checking_death);
		philo->last_meal = get_ms_since_epoch();
		pthread_mutex_unlock(philo->infos.checking_death);
		if (*(philo->infos.philo_running))
		{
			print_message(*philo, "is eating");
			safe_sleep(philo, philo->infos.time_to_eat);
			philo->meal_count++;
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(right_philo->fork);
		}
		else
		{
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(right_philo->fork);
		}
		if (simu_finished(philo))
			return NULL;
		print_message(*philo, "is sleeping");
		safe_sleep(philo, philo->infos.time_to_sleep);
		if (simu_finished(philo))
			return NULL;
		print_message(*philo, "is thinking");
	}
	return NULL;
}

int	end_of_philo(t_philo *head, int philo_count)
{
	int	finished_eating_count;
	int	i;

	if (!head->infos.time_to_die)
	{
		print_message(*head, "died");
		return (0);
	}
	usleep(head->infos.time_to_die);
	while (1)
	{
		finished_eating_count = 0;
		i = 1;
		while(i <= philo_count)
		{
			pthread_mutex_lock(head->infos.checking_death);
			if (head->infos.max_eat > 0 && head->meal_count >= head->infos.max_eat)
				finished_eating_count++;
			if (get_ms_since_epoch() - head->last_meal > head->infos.time_to_die)
			{
				print_message(*head, "died");
				pthread_mutex_unlock(head->infos.checking_death);
				return (0);
			}
			pthread_mutex_unlock(head->infos.checking_death);
			head = head->next;
			i++;
		}
		if (finished_eating_count == philo_count)
			return (0);
		usleep(1000);
	}
}
