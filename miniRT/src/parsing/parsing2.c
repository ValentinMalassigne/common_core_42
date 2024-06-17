/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:23:57 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/30 14:36:58 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../camera/camera.h"

t_list	*list_all(t_list *sp, t_list *pl, t_list *cyl, t_arena *arena)
{
	t_list		*all;

	all = NULL;
	while (sp)
	{
		ft_lstadd_back(&all, ft_lstnew(arena,
				convert_sph_to_obj(arena, (t_sphere *)sp->data)));
		sp = sp->next;
	}
	while (cyl)
	{
		ft_lstadd_back(&all, ft_lstnew(arena,
				convert_cyl_to_obj(arena, (t_cylinder *)cyl->data)));
		cyl = cyl->next;
	}
	while (pl)
	{
		ft_lstadd_back(&all, ft_lstnew(arena,
				convert_pln_to_obj(arena, (t_plane *)pl->data)));
		pl = pl->next;
	}
	return (all);
}

t_objects	*init_objects(t_arena *arena, char *argv[])
{
	t_objects	*objects;
	t_list		*params;

	params = parsing_to_list(arena, argv[1]);
	check_duplicated_capitals(arena, params);
	objects = arena_alloc(arena, sizeof(*objects));
	objects->camera = find_camera(arena, params, NULL);
	objects->ambient = find_ambient(arena, params, NULL);
	objects->light = find_light(arena, params, NULL);
	objects->spheres = find_spheres(arena, params);
	objects->planes = find_planes(arena, params);
	objects->cylinders = find_cylinders(arena, params);
	objects->sp_count = ft_lstsize(objects->spheres);
	objects->pl_count = ft_lstsize(objects->planes);
	objects->cy_count = ft_lstsize(objects->cylinders);
	objects->ob_count = objects->sp_count + objects->pl_count
		+ objects->cy_count;
	objects->all = list_all(objects->spheres, objects->planes,
			objects->cylinders, arena);
	return (objects);
}
