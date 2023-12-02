/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:00:45 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/02 10:59:37 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	clear_mutex(t_philo *philo_head, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_destroy(philo_head->fork);
		philo_head = philo_head->next;
		i++;
	}
}

void	free_list(t_philo *head, int philo_count)
{
	int		i;
	t_philo *temp;

	free(head->infos.philo_running);
	free(head->infos.lock_print);
	free(head->infos.checking_death);
	i = 0;
	while (i < philo_count)
	{
		temp = head;
		head = head->next;
		free(temp->fork);
		free(temp);
		i++;
	}
}
