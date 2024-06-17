/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:39:02 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/30 16:44:43 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

float	cap_inters(t_lightray ray, t_plane cap, float diameter, float t_min)
{
	t_vec3	p;
	float	denom;
	float	t_cap;

	denom = vec3_dot(ray.direction, cap.normal);
	if (fabs(denom) > 0.0001)
	{
		t_cap = vec3_dot(vec3_sub(cap.apoint, ray.origin), cap.normal) / denom;
		if (t_cap >= 0)
		{
			p = vec3_add(ray.origin, vec3_mul(ray.direction, t_cap));
			if (vec3_length(vec3_sub(p, cap.apoint)) <= diameter / 2)
				t_min = fmin(t_min, t_cap);
		}
	}
	return (t_min);
}

float	hit_cylinder_distance(t_object *cylinder, t_lightray ray)
{
	t_cylinder	*cy;
	t_vec3		a_vec;
	t_plane		topcap;
	t_plane		botcap;
	float		t_min;

	cy = (t_cylinder *)cylinder;
	a_vec = vec3_normalize(cy->normal);
	t_min = get_t_min(a_vec, ray.direction,
			vec3_sub(ray.origin, cy->center), cy);
	topcap.apoint = vec3_add(cy->center, vec3_mul(a_vec, cy->height));
	topcap.normal = a_vec;
	botcap.apoint = cy->center;
	botcap.normal = vec3_mul(a_vec, -1);
	t_min = cap_inters(ray, topcap, cy->diameter, t_min);
	t_min = cap_inters(ray, botcap, cy->diameter, t_min);
	if (t_min == INFINITY)
		return (-1);
	return (t_min);
}
