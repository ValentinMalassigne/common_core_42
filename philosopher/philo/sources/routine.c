/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:13:03 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/23 20:20:06 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*philo_routine(void *params)
{
	t_philo	*philo = (t_philo *) params;
	t_philo	*right_thparams = philo->next;

	pthread_mutex_lock(philo->mutex);
	printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
	pthread_mutex_lock(right_thparams->mutex);	
	printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);

	printf("%ld %d is eating\n", get_ms_since_epoch(), philo->number);
	usleep(1000000);
	printf("%ld %d finished eating\n", get_ms_since_epoch(), philo->number);
	
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_unlock(right_thparams->mutex);
	return NULL;
}
