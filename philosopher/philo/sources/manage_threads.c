/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:36:52 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/23 20:30:59 by vmalassi         ###   ########.fr       */
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

static int create_threads(pthread_t *thread_list, t_philo *philo_head, int philo_count)
{
	int	i;
	i = 0;
	while (i < philo_count)
	{
		if (pthread_create((thread_list + i), NULL, &philo_routine, (void *) philo_head) != 0)
			return (0);
		philo_head = philo_head->next;
		i++;
	}
	return (1);
}

int	manage_threads(t_philo *philo_head, int philo_count)
{

	pthread_t		*thread_list;

	thread_list = malloc(philo_count * sizeof(pthread_t));
	if (!thread_list)
	{
		printf("malloc error\n");
		return (1);
	}
	if (!create_threads(thread_list, philo_head, philo_count))
		return (1);
	join_threads(thread_list, philo_count);
	return (0);
}
