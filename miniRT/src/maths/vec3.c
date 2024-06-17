/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:49:01 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:49:03 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./maths.h"

t_vec3	vec3_add(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x + w.x, .y = v.y + w.y, .z = v.z + w.z};
	return (ret);
}

t_vec3	vec3_sub(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x - w.x, .y = v.y - w.y, .z = v.z - w.z};
	return (ret);
}

t_vec3	vec3_mul(t_vec3 v, float scalar)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar};
	return (ret);
}

t_vec3	vec3_div(t_vec3 v, float scalar)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x / scalar, .y = v.y / scalar, .z = v.z / scalar};
	return (ret);
}

float	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
