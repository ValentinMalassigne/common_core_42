/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:49:50 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/30 14:10:14 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cylinder	*create_cy2(t_cylinder *cylinder, char *delimiter, char **params)
{
	cylinder->diameter = ft_atof(params[2]);
	cylinder->height = ft_atof(params[3]);
	cylinder->color = color_int(
			ft_atoi(ft_strtok(params[4], delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter))
			);
	cylinder->bounce = NULL;
	cylinder->hit_dist = &hit_cylinder_distance;
	cylinder->type = 2;
	return (cylinder);
}

t_cylinder	*create_cylinder(t_arena *arena, char **params)
{
	char		*delimiter;
	t_cylinder	*cylinder;

	delimiter = ",";
	cylinder = (t_cylinder *)arena_alloc(arena, sizeof(t_cylinder));
	cylinder->center = (t_point3){
		ft_atof(ft_strtok(params[0], delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))
	};
	cylinder->normal = (t_vec3){
		ft_atof(ft_strtok(params[1], delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))
	};
	if (cylinder->normal.x < -1 || cylinder->normal.x > 1
		|| cylinder->normal.y < -1 || cylinder->normal.y > 1
		|| cylinder->normal.z < -1 || cylinder->normal.z > 1)
		free_and_exit_error(arena, "Invalid cylinder normal vector");
	return (create_cy2(cylinder, delimiter, params));
}

t_list	*get_cy_params2(t_arena *ar, t_list *tmp, t_list *cyl, char **params)
{
	t_cylinder	*cylinder;

	if (!float_in_range(ft_atof(params[2]), 0, __FLT_MAX__))
		free_and_exit_error(ar, "Invalid cylinder diameter");
	tmp = tmp->next;
	params[3] = str_is_float(ar, (char *)tmp->data,
			"Invalid cylinder height");
	if (!float_in_range(ft_atof(params[3]), 0, __FLT_MAX__))
		free_and_exit_error(ar, "Invalid cylinder height");
	tmp = tmp->next;
	params[4] = (char *)tmp->data;
	if (!is_rgb(params[4]))
		free_and_exit_error(ar, "Invalid cylinder color");
	cylinder = create_cylinder(ar, params);
	if (!cyl)
		cyl = ft_lstnew(ar, cylinder);
	else
		ft_lstadd_back(&cyl, ft_lstnew(ar, cylinder));
	return (cyl);
}

t_list	*get_cylinders_params(t_arena *arena, t_list *tmp, t_list *cylinders)
{
	char		*params[5];

	if (!tmp->data || !((t_list *)tmp->data)->next)
		free_and_exit_error(arena, "Invalid cylinder parameters");
	tmp = ((t_list *)tmp->data)->next;
	if (!tmp->next || !tmp->next->next || !tmp->next->next->next
		|| !tmp->next->next->next->next)
		free_and_exit_error(arena, "Invalid cylinder parameters");
	params[0] = (char *)tmp->data;
	if (!is_coordinates(params[0]))
		free_and_exit_error(arena, "Invalid cylinder center coordinates");
	tmp = tmp->next;
	params[1] = (char *)tmp->data;
	if (!is_coordinates(params[1]))
		free_and_exit_error(arena, "Invalid cylinder normal vector");
	tmp = tmp->next;
	params[2] = str_is_float(arena, (char *)tmp->data,
			"Invalid cylinder diameter");
	return (get_cy_params2(arena, tmp, cylinders, params));
}

t_list	*find_cylinders(t_arena *arena, t_list *list_params)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*cylinders;
	char		*str;

	tmp = list_params->next;
	cylinders = NULL;
	while (tmp)
	{
		tmp2 = tmp->data;
		str = (char *)tmp2->data;
		if (ft_strcmp(str, "cy") == 0)
			cylinders = get_cylinders_params(arena, tmp, cylinders);
		tmp = tmp->next;
	}
	return (cylinders);
}
