/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:40 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:41 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>
/* Vec3
================================================================================
*/
typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

// Alias for t_vec3.
typedef t_vec3	t_point3;

t_vec3	vec3_add(t_vec3 v, t_vec3 w);
t_vec3	vec3_sub(t_vec3 v, t_vec3 w);
t_vec3	vec3_mul(t_vec3 v, float scalar);
t_vec3	vec3_div(t_vec3 v, float scalar);
float	vec3_length_squared(t_vec3 v);
float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_dot(t_vec3 v, t_vec3 w);
t_vec3	vec3_cross(t_vec3 v, t_vec3 w);
t_vec3	vec3_mean(t_vec3 v, t_vec3 w);
t_vec3	vec3_coloradddue(t_vec3 color1, t_vec3 color2);
t_vec3	vec3_coloraddmax(t_vec3 color1, t_vec3 color2);
t_vec3	vec3_coloradddueamb(t_vec3 color1, t_vec3 color2);
t_vec3	vec3_coloradddue3(t_vec3 color1, t_vec3 colorlight, t_vec3 coloramb);
t_vec3	vec3_reflect(t_vec3 v, t_vec3 n);
/* Misc
================================================================================
*/
// Converts degrees to radians.
float	to_rad(float deg);
// Converts radians to degrees.
float	to_deg(float rad);

#endif
