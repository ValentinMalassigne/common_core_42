/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:18:42 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 17:17:09 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	basic_check(char *str, int i, int *comma, int *dot)
{
	if (str[i] == ',')
		*(comma) += 1;
	if (str[i] == '.')
		*(dot) += 1;
	if (str[i] == ',' && str[i + 1] == ',')
		return (0);
	if (str[i] == '.' && str[i + 1] == '.')
		return (0);
	if (str[i] == '.' && str[i + 1] == ',')
		return (0);
	if (str[i] == ',' && str[i + 1] == '.')
		return (0);
	return (1);
}

int	is_coordinates(char *str)
{
	int	i;
	int	comma;
	int	dot;

	i = 0;
	comma = 0;
	dot = 0;
	if (str[0] == '.' || str[0] == ',')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		if (!basic_check(str, i, &comma, &dot))
			return (0);
		if (dot > 3 || comma > 2 || (str[i] != ',' && str[i] != '-'
				&& str[i] != '.' && (str[i] < '0' || str[i] > '9')))
			return (0);
		if (str[i] == '-' && str[i - 1] != ',' && (i != 0 && str[i - 1] != ' '))
			return (0);
		i++;
	}
	if (comma != 2 || dot > 3 || str[i - 1] == ',')
		return (0);
	return (1);
}
