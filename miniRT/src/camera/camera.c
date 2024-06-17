/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:46:59 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/04 14:57:35 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./camera.h"
#include "canvas/canvas.h"
#include "engine/engine.h"
#include "objects/objects.h"
#include "libft.h"
#include "ray.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

void	camera_init_viewport(t_camera *cam, int canvas_width,
		int canvas_height, void *arena)
{
	float		focal_length;
	t_vec3		cam_u;
	t_vec3		cam_v;
	t_vec3		cam_w;
	t_vp_helper	vp;

	cam->vp = arena_alloc(arena, sizeof(*cam->vp));
	focal_length = vec3_length(vec3_sub(cam->look_at, cam->center));
	vp.width = 2 * focal_length * tanf(to_rad(cam->hfov) / 2);
	vp.height = vp.width * ((float)canvas_height / canvas_width);
	cam_w = vec3_normalize(vec3_sub(cam->look_at, cam->center));
	cam_u = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, cam_w));
	cam_v = vec3_cross(cam_w, cam_u);
	vp.u = vec3_mul(cam_u, vp.width);
	vp.v = vec3_mul(cam_v, -vp.height);
	cam->vp->pixel_du = vec3_div(vp.u, canvas_width);
	cam->vp->pixel_dv = vec3_div(vp.v, canvas_height);
	vp.upper_left = vec3_sub(vec3_add(cam->center, vec3_mul(cam_w,
					focal_length)), vec3_add(vec3_div(vp.u, 2),
				vec3_div(vp.v, 2)));
	cam->vp->pixel_00 = vec3_add(vp.upper_left, vec3_mul(vec3_add(
					cam->vp->pixel_du, cam->vp->pixel_dv), 0.5f));
}

t_camera	*camera_create(t_point3 center, t_vec3 direction, float hfov,
		void *arena)
{
	t_camera	*cam;

	cam = arena_alloc(arena, sizeof(*cam));
	cam->center = center;
	cam->look_at = vec3_add(center, direction);
	cam->hfov = hfov;
	return (cam);
}

t_vec3	cylinder_surface_normal(t_object *cy, t_vec3 hit_point,
	t_vec3 ray_direction)
{
	t_vec3	normal;
	float	hit_height;
	t_vec3	c0;
	t_vec3	closest_point_on_axis;

	c0 = vec3_sub(hit_point, cy->center);
	hit_height = vec3_dot(c0, cy->normal);
	if (fabs(hit_height - cy->height) < 1e-5)
		normal = cy->normal;
	else if (fabs(hit_height) < 1e-5)
		normal = vec3_mul(cy->normal, -1);
	else
	{
		closest_point_on_axis = vec3_add(cy->center,
				vec3_mul(cy->normal, hit_height));
		normal = vec3_normalize(vec3_sub(hit_point, closest_point_on_axis));
	}
	if (vec3_dot(normal, ray_direction) > 0)
		normal = vec3_mul(normal, -1);
	return (normal);
}

t_point3	get_pixel_center(t_camera *cam, int i, int j)
{
	t_point3	pixel_center;

	pixel_center = vec3_add(cam->vp->pixel_00,
			vec3_add(vec3_mul(cam->vp->pixel_du, (float)i),
				vec3_mul(cam->vp->pixel_dv, (float)j)));
	return (pixel_center);
}

t_vec3	iter_objects(t_shade_iter_helper params, t_vec3 final_color)
{
	t_list		*object;
	t_object	*shadow_obj;
	float		distance;

	object = params.rd->objects->all;
	while (object)
	{
		shadow_obj = (t_object *)object->data;
		if (shadow_obj != params.obj && shadow_obj->type != 3)
		{
			distance = shadow_obj->hit_dist(shadow_obj,
					params.ray);
			if (distance > 1e-6f && distance < params.distance_to_light)
			{
				final_color = color_to_vec3(params.ray.color);
				final_color = vec3_coloradddue(final_color,
						params.ambient_color);
				break ;
			}
		}
		object = object->next;
	}
	return (final_color);
}
