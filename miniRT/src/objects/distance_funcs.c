/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/30 16:59:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

float	hit_sphere_distance(t_object *sphere, t_lightray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray.origin, sphere->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - pow(sphere->diameter / 2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant <= 0 || a == 0)
		return (-1);
	return ((-b - sqrtf(discriminant)) / (2 * a));
}

float	hit_plane_distance(t_object *plane, t_lightray ray)
{
	float	denom;
	float	t;

	denom = vec3_dot(ray.direction, ((t_plane *)plane)->normal);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub(((t_plane *)plane)->apoint, ray.origin),
				((t_plane *)plane)->normal)
			/ denom;
		ray.color = color_vec3(vec3_coloradddue(color_to_vec3(ray.color),
					color_to_vec3(((t_plane *)plane)->color)));
		if (t >= 0)
			return (t);
	}
	return (-1);
}

// t_vec3 vecs[3] = t_vec3 a_vec, t_vec3 d, t_vec3 co
float	get_discriminant(float values[5], t_vec3 vecs[3], t_cylinder *cy)
{
	t_vec3		a_perp;
	t_vec3		b_perp;

	a_perp = vec3_sub(vecs[1], vec3_mul(vecs[0], vec3_dot(vecs[1], vecs[0])));
	b_perp = vec3_sub(vecs[2], vec3_mul(vecs[0], vec3_dot(vecs[2], vecs[0])));
	values[0] = vec3_dot(a_perp, a_perp);
	values[1] = 2 * vec3_dot(a_perp, b_perp);
	values[2] = vec3_dot(b_perp, b_perp) - pow(cy->diameter / 2, 2);
	return (values[1] * values[1] - 4 * values[0] * values[2]);
}

//0 a, 1 b, 2 c, 3 discminant, 4 sqrt_discriminant
//temps 0 : t0, 1 : t1, 2 : y0, 3 : y1
float	get_t_min(t_vec3 a_vec, t_vec3 d, t_vec3 co, t_cylinder *cy)
{
	float		values[5];
	float		t_min;
	float		temps[4];

	temps[0] = INFINITY;
	temps[1] = INFINITY;
	t_min = INFINITY;
	values[3] = get_discriminant(values, (t_vec3[3]){a_vec, d, co}, cy);
	if (values[3] >= 0 && values[0] != 0)
	{
		values[4] = sqrtf(values[3]);
		temps[0] = (-values[1] - values[4]) / (2 * values[0]);
		temps[1] = (-values[1] + values[4]) / (2 * values[0]);
		temps[2] = vec3_dot(vec3_add(co, vec3_mul(d, temps[0])), a_vec);
		temps[3] = vec3_dot(vec3_add(co, vec3_mul(d, temps[1])), a_vec);
		if ((temps[2] >= 0 && temps[2] <= cy->height) && temps[0] > 0)
			t_min = fmin(t_min, temps[0]);
		if ((temps[3] >= 0 && temps[3] <= cy->height) && temps[1] > 0)
			t_min = fmin(t_min, temps[1]);
	}
	return (t_min);
}
