/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:36:52 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/04 13:40:41 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	join_threads(pthread_t *thread_list, int p_count)
{
	int	i;

	i = 0;
	while (i < p_count)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

static int	create_th(pthread_t *list, t_philo *head, int count, int *running)
{
	int	i;

	i = 0;
	while (i < count)
	{
		head->infos.philo_running = running;
		if (pthread_create((list + i), NULL,
				&philo_routine, (void *) head) != 0)
			return (0);
		head = head->next;
		i++;
		usleep(10);
	}
	return (1);
}

int	manage_threads(t_philo *philo_head, int p_count)
{
	pthread_t	*thread_list;
	int			*philo_running;
	int			res;

	thread_list = malloc(p_count * sizeof(pthread_t));
	if (!thread_list)
	{
		printf("malloc error\n");
		return (0);
	}
	philo_running = philo_head->infos.philo_running;
	if (!create_th(thread_list, philo_head, p_count, philo_running))
		return (0);
	res = end_of_philo(philo_head, p_count);
	pthread_mutex_lock(philo_head->infos.lock_print);
	*philo_running = res;
	pthread_mutex_unlock(philo_head->infos.lock_print);
	join_threads(thread_list, p_count);
	free(thread_list);
	return (1);
}

static int	check_death(t_philo *head, int	*finished_eating_count)
{
	pthread_mutex_lock(head->infos.checking_death);
	if (head->infos.max_eat > 0 && head->meal_count >= head->infos.max_eat)
		*(finished_eating_count) += 1;
	if (get_ms_since_epoch() - head->last_meal > head->infos.time_to_die)
	{
		print_message(*head, "died");
		pthread_mutex_unlock(head->infos.checking_death);
		return (0);
	}
	pthread_mutex_unlock(head->infos.checking_death);
	return (1);
}

int	end_of_philo(t_philo *head, int p_count)
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
		while (i <= p_count)
		{
			if (!check_death(head, &finished_eating_count))
				return (0);
			head = head->next;
			i++;
		}
		if (finished_eating_count == p_count)
			return (0);
		usleep(1000);
	}
}
