/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:22 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:47:24 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static float	clamp_f(float x, float min, float max)
{
	if (x < min)
		return (min);
	else if (x > max)
		return (max);
	else
		return (x);
}

t_color	color_vec3(t_vec3 v)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (uint8_t)(clamp_f(v.x * 255, 0, 255));
	g = (uint8_t)(clamp_f(v.y * 255, 0, 255));
	b = (uint8_t)(clamp_f(v.z * 255, 0, 255));
	return (r << 16 | g << 8 | b);
}

t_color	color_int(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

t_vec3	color_to_vec3(t_color c)
{
	t_vec3	v;

	v.x = (float)((c & 0xFF0000) >> 16) / 255.f;
	v.y = (float)((c & 0xFF00) >> 8) / 255.f;
	v.z = (float)(c & 0xFF) / 255.f;
	return (v);
}
