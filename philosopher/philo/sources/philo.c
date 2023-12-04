/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:20:29 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/04 13:14:46 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_infos		infos;
	int			p_count;
	t_philo		*philo_head;

	if (!parse_input(argc, argv, &infos, &p_count))
		return (0);
	if (!set_up_p_list(&philo_head, infos, p_count))
		return (0);
	if (!manage_threads(philo_head, p_count))
		return (0);
	clear_mutex(philo_head, p_count);
	free_list(philo_head, p_count);
	return (0);
}
