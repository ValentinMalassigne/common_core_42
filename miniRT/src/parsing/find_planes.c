/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:44:55 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/30 12:31:39 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_plane	*create_plane(t_arena *arena, char **params)
{
	char		*delimiter;
	t_plane		*plane;

	delimiter = ",";
	plane = (t_plane *)arena_alloc(arena, sizeof(t_plane));
	plane->apoint = (t_point3){
		ft_atof(ft_strtok(params[0], delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))
	};
	plane->normal = (t_vec3){ft_atof(ft_strtok(params[1], delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))};
	plane->normal = vec3_normalize(plane->normal);
	if (!float_in_range(plane->normal.x, -1, 1) || !float_in_range(
			plane->normal.y, -1, 1) || !float_in_range(plane->normal.z, -1, 1))
		free_and_exit_error(arena, "Invalid plane normal vector");
	plane->color = color_int(ft_atoi(ft_strtok(params[2], delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter))
			);
	plane->bounce = NULL;
	plane->hit_dist = &hit_plane_distance;
	plane->type = 3;
	return (plane);
}

t_list	*get_plane_params(t_arena *arena, t_list *tmp, t_list *planes)
{
	t_plane		*plane;
	char		*params[3];

	if (!tmp->data || !((t_list *)tmp->data)->next
		|| !((t_list *)((t_list *)tmp->data)->next)->next
		|| !((t_list *)((t_list *)((t_list *)tmp->data)->next)->next)->next)
		free_and_exit_error(arena, "Invalid plane parameters");
	tmp = ((t_list *)tmp->data)->next;
	params[0] = (char *)tmp->data;
	if (!is_coordinates(params[0]))
		free_and_exit_error(arena, "Invalid plane coordinates");
	tmp = tmp->next;
	params[1] = (char *)tmp->data;
	if (!is_coordinates(params[0]))
		free_and_exit_error(arena, "Invalid plane normal vector");
	tmp = tmp->next;
	params[2] = (char *)tmp->data;
	if (!is_rgb(params[2]))
		free_and_exit_error(arena, "Invalid plane color");
	plane = create_plane(arena, params);
	if (!planes)
		planes = ft_lstnew(arena, plane);
	else
		ft_lstadd_back(&planes, ft_lstnew(arena, plane));
	return (planes);
}

t_list	*find_planes(t_arena *arena, t_list *list_params)
{
	t_list		*tmp;
	t_list		*planes;
	char		*str;

	tmp = list_params->next;
	planes = NULL;
	while (tmp)
	{
		str = (char *)((t_list *) tmp->data)->data;
		if (ft_strcmp(str, "pl") == 0)
			planes = get_plane_params(arena, tmp, planes);
		tmp = tmp->next;
	}
	return (planes);
}
