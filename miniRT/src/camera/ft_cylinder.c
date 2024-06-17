/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:48:43 by aramier           #+#    #+#             */
/*   Updated: 2024/03/05 15:55:26 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_solutions	check_intersections(t_cylinder *cyl, t_ray ray, t_solutions ret,
		double m[2])
{
	t_point	x;

	x = vec_substract(ray.origin, cyl->axe_pos);
	m[0] = vec_point(ray.direction, cyl->orientation) * ret.t1 + vec_point(x,
			cyl->orientation);
	m[1] = vec_point(ray.direction, cyl->orientation) * ret.t2 + vec_point(x,
			cyl->orientation);
	if (m[0] < 0 || m[0] > cyl->height)
		ret.t1 = __DBL_MAX__;
	if (m[1] < 0 || m[1] > cyl->height)
		ret.t2 = __DBL_MAX__;
	return (ret);
}

t_solutions	ft_intersect_cylinder(void *data, t_ray ray)
{
	t_solutions	ret;
	t_point		x;
	double		k[4];
	double		m[2];
	t_cylinder	*cyl;

	cyl = data;
	x = vec_substract(ray.origin, cyl->axe_pos);
	k[0] = vec_point(ray.direction, ray.direction)
		- powf(vec_point(ray.direction, cyl->orientation), 2);
	k[1] = (vec_point(ray.direction, x)
			- vec_point(ray.direction, cyl->orientation) * vec_point(x,
				cyl->orientation)) * 2.0;
	k[2] = vec_point(x, x) - powf(vec_point(x, cyl->orientation), 2)
		- powf(cyl->diam / 2.0, 2);
	k[3] = k[1] * k[1] - 4 * k[0] * k[2];
	if (k[3] < 0)
		return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
	ret.t1 = (-k[1] + sqrtf(k[3])) / (2.0 * k[0]);
	ret.t2 = (-k[1] - sqrtf(k[3])) / (2.0 * k[0]);
	return (check_intersections(cyl, ray, ret, m));
}

t_point	ft_cylinder_normal(void *data, t_point intersection, t_ray ray)
{
	t_cylinder	*cyl;
	double		t;
	t_point		pt;

	cyl = data;
	t = vec_point(vec_substract(intersection, cyl->bottom), cyl->orientation);
	pt = vec_add(cyl->bottom, vec_mul(t, cyl->orientation));
	return (ft_rotate_normal(ray, vec_substract(intersection, pt),
			intersection));
}

t_obj	*ft_create_cylinder(t_cy_params params, t_exvar *var)
{
	t_cylinder	*cyl;
	t_obj		*obj;

	cyl = ft_malloc_save(sizeof(t_cylinder), var);
	obj = ft_malloc_save(sizeof(t_obj), var);
	cyl->axe_pos = params.axe_pos;
	cyl->orientation = vec_norm(params.orient);
	cyl->diam = params.diam;
	cyl->height = params.height;
	cyl->bottom = vec_add(cyl->axe_pos, vec_mul(cyl->height,
				cyl->orientation));
	obj->data = cyl;
	obj->type = CYLINDER;
	obj->ft_intersect = ft_intersect_cylinder;
	obj->ft_get_norm = ft_cylinder_normal;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}
