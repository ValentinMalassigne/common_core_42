/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:23 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/30 16:42:40 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "color/color.h"
# include "libft.h"
# include "maths/maths.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_lightray
{
	t_point3	origin;
	t_vec3		direction;
	t_color		color;
}				t_lightray;

typedef struct s_object	t_object;
typedef struct s_object
{
	t_point3	center;
	t_vec3		normal;
	float		diameter;
	float		height;
	t_color		color;
	t_lightray	(*bounce)(t_object * obj, t_lightray ray);
	float		(*hit_dist)(t_object *obj, t_lightray ray);
	int			type;
}				t_object;

typedef struct s_sphere
{
	t_point3	center;
	float		diameter;
	t_color		color;
	t_lightray	(*bounce)(t_object * obj, t_lightray ray);
	float		(*hit_dist)(t_object *obj, t_lightray ray);
	int			type;
}				t_sphere;

typedef struct s_plane
{
	t_point3	apoint;
	t_vec3		normal;
	t_color		color;
	t_lightray	(*bounce)(t_object * obj, t_lightray ray);
	float		(*hit_dist)(t_object *obj, t_lightray ray);
	int			type;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		normal;
	float		diameter;
	float		height;
	t_color		color;
	t_lightray	(*bounce)(t_object * obj, t_lightray ray);
	float		(*hit_dist)(t_object *obj, t_lightray ray);
	int			type;
}				t_cylinder;

float	hit_sphere_distance(t_object *sphere, t_lightray ray);
float	hit_plane_distance(t_object *plane, t_lightray ray);
float	hit_cylinder_distance(t_object *cylinder, t_lightray ray);
float	get_t_min(t_vec3 a_vec, t_vec3 d, t_vec3 co, t_cylinder *cy);

#endif // !OBJECTS_H