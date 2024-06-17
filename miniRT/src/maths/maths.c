/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:35 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:36 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./maths.h"
#include <math.h>

float	to_rad(float deg)
{
	return ((float)(deg * M_PI / 180.0));
}

float	to_deg(float rad)
{
	return ((float)(rad * 180.0 / M_PI));
}
