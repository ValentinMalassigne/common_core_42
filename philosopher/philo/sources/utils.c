/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:17:24 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/20 17:12:45 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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