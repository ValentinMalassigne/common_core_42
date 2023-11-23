/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:18:54 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/23 20:32:25 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_infos {
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int max_eat;
} t_infos;

typedef struct s_philo {
	int				number;
	struct s_infos	infos;
	pthread_mutex_t	*mutex;
	struct s_philo	*next;
	struct s_philo	*prev;
} t_philo;

int		ft_atoi(char *str);
int		ft_is_numeric(char *str);
int		parse_inputs(int argc, char **argv, t_infos *infos, int *philo_count);
int		manage_threads(t_philo *philo_head, int philo_count);
void	*philo_routine(void *params);
long	get_ms_since_epoch(void);
void	clear_mutex(t_philo *philo_head, int philo_count);
t_philo	*set_up_philo_list(t_philo **philo_head, t_infos infos, int philo_count);

#endif