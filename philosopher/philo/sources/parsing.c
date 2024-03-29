/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:11:42 by vmalassi          #+#    #+#             */
/*   Updated: 2023/12/04 13:41:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static long	ft_atol(const char *nptr)
{
	long	res;
	int		signe;

	res = 0;
	signe = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
	{
		signe = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while ('0' <= *nptr && *nptr <= '9')
		res = res * 10 + *nptr++ - '0';
	return (res * signe);
}

static int	int_overflow(char *str)
{
	long	value;

	value = ft_atol(str);
	if (value < -2147483648 || value > 2147483647)
		return (1);
	return (0);
}

static int	check_num_and_overflow(char *str)
{
	if (!ft_is_numeric(str))
	{
		printf("Error : Wrong argument format\n");
		printf("All arguments must be positive integers\n");
		return (0);
	}
	else if (int_overflow(str))
	{
		printf("Error : Wrong argument format\n");
		printf("Arguments must not overflow an int\n");
		return (0);
	}
	return (1);
}

static int	verify_inputs(int argc, char **argv)
{
	int	i;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			if (!check_num_and_overflow(argv[i]))
				return (0);
			i++;
		}
	}
	else
	{
		printf("Error : Wrong number of arguments\n");
		printf("Accepted arguments : number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep\n");
		printf("[optional] number_of_times_each_philosopher_must_eat\n");
		printf("All arguments must be positive integers\n");
		return (0);
	}
	return (1);
}

int	parse_input(int argc, char **argv, t_infos *infos, int *p_count)
{
	if (verify_inputs(argc, argv))
	{
		*p_count = ft_atoi(argv[1]);
		if (!*p_count)
		{
			printf("Error : Invalid number of philosopers\n");
			return (0);
		}
		infos->time_to_die = ft_atoi(argv[2]);
		infos->time_to_eat = ft_atoi(argv[3]);
		infos->time_to_sleep = ft_atoi(argv[4]);
		infos->philo_running = NULL;
		infos->lock_print = NULL;
		infos->checking_death = NULL;
		if (argc == 6)
			infos->max_eat = ft_atoi(argv[5]);
		else
			infos->max_eat = -1;
		return (1);
	}
	return (0);
}
