/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:07 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/04 16:40:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "maths/maths.h"
# include "parsing/parsing.h"
# include "libft.h"
# include "objects/objects.h"

/* Basic camera with a viewport fixed to it.
The viewport is orthogonal to the camera direction, its center is placed where
the camera is looking at.
*/

# define M_PI 3.14159265358979323846

typedef struct s_camera
{
	t_point3			center;
	t_point3			look_at;
	float				hfov;
	struct				s_viewport
	{
		t_point3		pixel_00;
		t_vec3			pixel_du;
		t_vec3			pixel_dv;
	} *vp;
}						t_camera;

t_camera				*camera_create(t_point3 center, t_vec3 direction,
							float hfov, void *arena);

void					camera_init_viewport(t_camera *cam, int canvas_width,
							int canvas_height, void *arena);

void					*camera_render(void *vargp);

t_camera				*find_camera(t_arena *arena, t_list *list, char *str);
/* INTERNAL
================================================================================
*/

typedef struct t_objects
{
	t_list				*spheres;
	t_list				*planes;
	t_list				*cylinders;
	t_light				*light;
	t_camera			*camera;
	t_ambient			*ambient;
	int					sp_count;
	int					pl_count;
	int					cy_count;
	int					ob_count;
	t_list				*all;
}					t_objects;

typedef struct s_engine	t_engine;
typedef struct s_canvas	t_canvas;
typedef struct s_render
{
	t_camera			*camera;
	t_canvas			*canvas;
	t_engine			*engine;
	t_objects			*objects;
	t_arena				*arena;
}						t_render;

// Because we are limited to 5 var declarations / function
typedef struct s_vp_helper
{
	float				width;
	float				height;
	t_vec3				u;
	t_vec3				v;
	t_point3			upper_left;
}						t_vp_helper;

typedef struct s_calc_obj_helper
{
	t_vec3		final_color;
	int			i;
	int			j;
}			t_calc_obj_helper;

typedef struct s_comp_shade_helper
{
	t_render	*rd;
	t_object	*obj;
	t_vec3		hit_point;
	t_vec3		ray_direction;
	t_vec3		ambient_color;
	t_objects	*objects;
}			t_comp_shade_helper;

typedef struct s_shade_iter_helper
{
	t_render	*rd;
	t_object	*obj;
	t_lightray	ray;
	float		distance_to_light;
	t_vec3		ambient_color;
}			t_shade_iter_helper;

t_objects				*init_objects(t_arena *arena, char *argv[]);
t_point3				get_pixel_center(t_camera *cam, int i, int j);
t_vec3					cylinder_surface_normal(t_object *cy, t_vec3 hit_point,
							t_vec3 ray_direction);
t_vec3					iter_objects(t_shade_iter_helper params,
							t_vec3 final_color);
t_vec3					calc_objects(t_render *rd, int i, int j);
#endif
