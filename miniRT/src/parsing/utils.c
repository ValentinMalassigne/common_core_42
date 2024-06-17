/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:01:52 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 17:17:50 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_duplicated_capitals(t_arena *arena, t_list *params)
{
	t_list	*tmp;
	int		a_count;
	int		c_count;
	int		l_count;

	a_count = 0;
	c_count = 0;
	l_count = 0;
	tmp = params->next;
	while (tmp)
	{
		if (ft_strcmp(((t_list *)tmp->data)->data, "A") == 0)
			a_count++;
		if (ft_strcmp(((t_list *)tmp->data)->data, "C") == 0)
			c_count++;
		if (ft_strcmp(((t_list *)tmp->data)->data, "L") == 0)
			l_count++;
		tmp = tmp->next;
	}
	if (a_count > 1)
		free_and_exit_error(arena, "too many ambient lightning");
	if (c_count > 1)
		free_and_exit_error(arena, "too many cameras");
	if (l_count > 1)
		free_and_exit_error(arena, "too many lights");
}

char	*str_is_float(t_arena *arena, char *str, char *msg)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (dot > 1 || (str[i] != '.' && (str[i] < '0' || str[i] > '9')))
		{
			if (str[i] != '\n' || (str[i] == '\n' && str[i + 1])
				|| (str[i] == '\n' && i == 0))
				free_and_exit_error(arena, msg);
		}
		i++;
	}
	return (str);
}

int	float_in_range(float value, float min, float max)
{
	if (value >= min && value <= max)
		return (1);
	return (0);
}

int	is_rgb(char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (str[0] == '.' || str[0] == ',')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		if (str[i] == ',')
			comma++;
		if (str[i] == ',' && str[i + 1] == ',')
			return (0);
		if (comma > 2 || (str[i] != ',' && (str[i] < '0' || str[i] > '9')))
			return (0);
		i++;
	}
	if (comma != 2 || str[i - 1] == ',')
		return (0);
	return (1);
}

t_vec3	extract_rgb(t_arena *arena, char *str, char *msg)
{
	t_vec3	vec;
	char	*token;

	token = ft_strtok(str, ",");
	if (!float_in_range(ft_atof(token), 0, 255))
		free_and_exit_error(arena, msg);
	vec.x = ft_atof(token) / 255;
	token = ft_strtok(NULL, ",");
	if (!float_in_range(ft_atof(token), 0, 255))
		free_and_exit_error(arena, msg);
	vec.y = ft_atof(token) / 255;
	token = ft_strtok(NULL, ",");
	if (!float_in_range(ft_atof(token), 0, 255))
		free_and_exit_error(arena, msg);
	vec.z = ft_atof(token) / 255;
	return (vec);
}
