/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:17:24 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/02 11:27:25 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_atoi(char *str)
{
	int	res;
	int	signe;

	res = 0;
	signe = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res * signe);
}

int	ft_is_numeric(char *str)
{
	while(*str)
	{
		if (*str < 48 || *str > 57)
			return (0);
		str++;
	}
	return (1);
}

long long	get_ms_since_epoch(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	print_message(t_philo philo, char *msg)
{
	pthread_mutex_lock(philo.infos.lock_print);
	if (*(philo.infos.philo_running))
		printf("%07lld %d %s\n",get_ms_since_epoch() - philo.infos.start_time, philo.number, msg);
	pthread_mutex_unlock(philo.infos.lock_print);
}
