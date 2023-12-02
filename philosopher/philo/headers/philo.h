/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:18:54 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/02 11:20:34 by vmalassi         ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			max_eat;
	long long		start_time;
	int				*philo_running;
	pthread_mutex_t	*lock_print;
	pthread_mutex_t	*checking_death;
} t_infos;

typedef struct s_philo {
	int				number;
	int				meal_count;
	long			last_meal;
	struct s_infos	infos;
	pthread_mutex_t	*fork;
	struct s_philo	*next;
} t_philo;

int			ft_atoi(char *str);
int			ft_is_numeric(char *str);
int			parse_inputs(int argc, char **argv, t_infos *infos, int *philo_count);
int			manage_threads(t_philo *philo_head, int philo_count);
int			end_of_philo(t_philo *head, int philo_count);
void		*philo_routine(void *params);
void		clear_mutex(t_philo *philo_head, int philo_count);
void		free_list(t_philo *head, int philo_count);
void		print_message(t_philo philo, char *msg);
t_philo		*set_up_philo_list(t_philo **philo_head, t_infos infos, int philo_count);
long long	get_ms_since_epoch(void);

#endif