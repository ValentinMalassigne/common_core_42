/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:50:01 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/17 17:07:05 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static void	zoom(t_fractol *fractol, double zoom)
{
	double	length_r;
	double	length_i;

	length_r = fractol->min_r - fractol->max_r;
	length_i = fractol->max_i - fractol->min_i;
	fractol->max_r = fractol->max_r + (length_r - zoom * length_r) / 2;
	fractol->min_r = fractol->max_r + zoom * length_r;
	fractol->min_i = fractol->min_i + (length_i - zoom * length_i) / 2;
	fractol->max_i = fractol->min_i + zoom * length_i;
}

int	key_event(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		end_fractol(fractol);
	else
		return (0);
	render(fractol);
	return (0);
}

int	mouse_event(int keycode, int x, int y, t_fractol *fractol)
{
	x += y;
	if (keycode == MOUSE_WHEEL_UP)
		zoom(fractol, 0.5);
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(fractol, 2);
	else
		return (0);
	render(fractol);
	return (0);
}
