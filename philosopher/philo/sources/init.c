/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:16:05 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/04 13:18:40 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static t_philo	*last_philo(t_philo *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	add_node_back(t_philo **head, t_philo *new_philo)
{
	t_philo	*temp;

	if (*head == NULL)
		*head = new_philo;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_philo;
	}
}

static t_philo	*new_philo_node(int number, t_infos infos, int *philo_running)
{
	t_philo			*new_philo;
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	new_philo = malloc(sizeof(t_philo));
	if (!fork || !new_philo)
		return (NULL);
	pthread_mutex_init(fork, NULL);
	new_philo->number = number;
	new_philo->fork = fork;
	new_philo->infos = infos;
	new_philo->meal_count = 0;
	new_philo->last_meal = get_ms_since_epoch();
	new_philo->next = NULL;
	new_philo->infos.philo_running = philo_running;
	return (new_philo);
}

static int	init_infos_and_running(t_infos *infos, int *philo_running)
{
	if (!philo_running)
		return (0);
	infos->checking_death = malloc(sizeof(pthread_mutex_t));
	if (!infos->checking_death)
	{
		free(philo_running);
		return (0);
	}
	infos->lock_print = malloc(sizeof(pthread_mutex_t));
	if (!infos->lock_print)
	{
		free(philo_running);
		free(infos->checking_death);
		return (0);
	}
	*philo_running = 1;
	infos->start_time = get_ms_since_epoch();
	pthread_mutex_init(infos->checking_death, NULL);
	pthread_mutex_init(infos->lock_print, NULL);
	return (1);
}

t_philo	*set_up_p_list(t_philo **philo_head, t_infos infos, int p_count)
{
	t_philo	*temp_philo;
	int		*philo_running;
	int		i;

	*philo_head = NULL;
	philo_running = malloc(sizeof(int));
	if (!init_infos_and_running(&infos, philo_running))
		return (NULL);
	i = 1;
	while (i <= p_count)
	{
		temp_philo = new_philo_node(i, infos, philo_running);
		if (!temp_philo)
			return (NULL);
		add_node_back(philo_head, temp_philo);
		i++;
	}
	temp_philo = last_philo(*philo_head);
	temp_philo->next = *philo_head;
	return (*philo_head);
}
