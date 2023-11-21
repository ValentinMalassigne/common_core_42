/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:18:54 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/21 15:52:37 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo {
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
} t_philo;

typedef struct s_infos {
	int number_of_philosophers;
	int max_eat;
} t_infos;

int	ft_atoi(char *str);
int	ft_is_numeric(char *str);

#endif