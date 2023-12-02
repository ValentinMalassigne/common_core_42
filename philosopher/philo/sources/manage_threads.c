/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:36:52 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/02 12:05:24 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	join_threads(pthread_t * thread_list, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

static int create_threads(pthread_t *thread_list, t_philo *philo_head, int philo_count, int *philo_running)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		philo_head->infos.philo_running = philo_running;
		if (pthread_create((thread_list + i), NULL, &philo_routine, (void *) philo_head) != 0)
			return (0);
		philo_head = philo_head->next;
		i++;
		usleep(10);
	}
	return (1);
}

int	manage_threads(t_philo *philo_head, int philo_count)
{
	pthread_t	*thread_list;
	int			*philo_running;
	int 		res;

	thread_list = malloc(philo_count * sizeof(pthread_t));
	if (!thread_list)
	{
		printf("malloc error\n");
		return (0);
	}
	philo_running = philo_head->infos.philo_running;
	if (!create_threads(thread_list, philo_head, philo_count, philo_running))
		return (0);
	res = end_of_philo(philo_head, philo_count);
	pthread_mutex_lock(philo_head->infos.lock_print);
	*philo_running = res;
	pthread_mutex_unlock(philo_head->infos.lock_print);
	join_threads(thread_list, philo_count);
	free(thread_list);
	return (1);
}
