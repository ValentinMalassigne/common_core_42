/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:21 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:22 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

typedef struct s_timer
{
	long long	time_start;
}	t_timer;

// Timer is initialized with time at creation
t_timer	*rt_timer_create(void *arena);

// Sleep for the specified number of milliseconds
void	timer_delay(int ms);

// get time (in ms) elapsed since creation of timer
int		timer_get_ticks(t_timer *timer);

#endif
