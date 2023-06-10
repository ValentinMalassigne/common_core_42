/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:51:48 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int		ft_is_number(char *str);
long	ft_atol(const char *nptr);
int		ft_is_larger_than_int(char *str);
int		ft_found_a_duplicate(char **argv, int start, int length);

int	input_is_correct(int argc, char **argv, int start_index)
{
	int	i;

	i = start_index;
	while (i < argc)
	{
		if (!ft_is_number(argv[i]) || ft_is_larger_than_int(argv[i])
			|| ft_found_a_duplicate(argv, i, argc))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	ft_is_larger_than_int(char *str)
{
	long	value;

	value = ft_atol(str);
	if (value < -2147483648 || value > 2147483647)
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
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

int	ft_found_a_duplicate(char **argv, int start, int length)
{
	int	i;

	i = start + 1;
	while (i < length)
	{
		if (ft_atoi(argv[start]) == ft_atoi(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
