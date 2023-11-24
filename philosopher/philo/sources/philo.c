/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:20:29 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/24 19:50:29 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_infos 	infos;
	int			philo_count;
	t_philo		*philo_head;

	if (!parse_inputs(argc, argv, &infos, &philo_count))
		return (0);
	if (!set_up_philo_list(&philo_head, infos, philo_count))
		return (0);
	if (!manage_threads(philo_head, philo_count))
		return (0);
	clear_mutex(philo_head, philo_count);
	free_list(philo_head, philo_count);
	return(0);
}
