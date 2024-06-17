/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:46:27 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/29 11:37:24 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./maths.h"

t_vec3	vec3_mean(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = (v.x + w.x) / 2, .y = (v.y + w.y) / 2, .z = (v.z + w.z)
		/ 2};
	return (ret);
}

t_vec3	vec3_coloradddue(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;

	if (color1.x == 0 || color2.x == 0)
		result.x = 0;
	else
		result.x = fminf(color1.x, color2.x);
	if (color1.y == 0 || color2.y == 0)
		result.y = 0;
	else
		result.y = fminf(color1.y, color2.y);
	if (color1.z == 0 || color2.z == 0)
		result.z = 0;
	else
		result.z = fminf(color1.z, color2.z);
	return (result);
}

t_vec3	vec3_coloradddue3(t_vec3 color1, t_vec3 colorlight, t_vec3 coloramb)
{
	t_vec3	result;

	if (color1.x == 0 || (colorlight.x == 0 && coloramb.x == 0))
		result.x = 0;
	else
		result.x = fmaxf(fmaxf(color1.x, colorlight.x), coloramb.x);
	if (color1.y == 0 || (colorlight.y == 0 && coloramb.y == 0))
		result.y = 0;
	else
		result.y = fmaxf(fmaxf(color1.y, colorlight.y), coloramb.y);
	if (color1.z == 0 || (colorlight.z == 0 && coloramb.z == 0))
		result.z = 0;
	else
		result.z = fmaxf(fmaxf(color1.z, colorlight.z), coloramb.z);
	return (result);
}

t_vec3	vec3_coloradddueamb(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;

	if (color1.x == 0 && color2.x == 0)
		result.x = 0;
	else
		result.x = fmax(color1.x / 2 + color2.x / 2, 0.99999f);
	if (color1.y == 0 && color2.y == 0)
		result.y = 0;
	else
		result.y = fmax(color1.y / 2 + color2.y / 2, 0.99999f);
	if (color1.z == 0 && color2.z == 0)
		result.z = 0;
	else
		result.z = fmax(color1.z / 2 + color2.z / 2, 0.99999f);
	return (result);
}

t_vec3	vec3_coloraddmax(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;

	result = vec3_add(color1, color2);
	if (result.x > 0.99999999f)
		result.x = 0.99999999f;
	if (result.y > 0.99999999f)
		result.y = 0.99999999f;
	if (result.z > 0.99999999f)
		result.z = 0.99999999f;
	return (result);
}
