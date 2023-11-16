/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:50:01 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/16 17:27:08 by vmalassi         ###   ########.fr       */
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

static void	move(t_fractol *fractol, double distance, char direction)
{
	double	length_r;
	double	length_i;

	length_r = fractol->max_r - fractol->min_r;
	length_i = fractol->max_i - fractol->min_i;
	if (direction == 'R')
	{
		fractol->min_r += length_r * distance;
		fractol->max_r += length_r * distance;
	}
	else if (direction == 'L')
	{
		fractol->min_r -= length_r * distance;
		fractol->max_r -= length_r * distance;
	}
	else if (direction == 'D')
	{
		fractol->min_i -= length_i * distance;
		fractol->max_i -= length_i * distance;
	}
	else if (direction == 'U')
	{
		fractol->min_i += length_i * distance;
		fractol->max_i += length_i * distance;
	}
}

int	key_event(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		end_fractol(fractol);
	else if (keycode == KEY_UP)
		move(fractol, 0.2, 'U');
	else if (keycode == KEY_DOWN)
		move(fractol, 0.2, 'D');
	else if (keycode == KEY_LEFT)
		move(fractol, 0.2, 'L');
	else if (keycode == KEY_RIGHT)
		move(fractol, 0.2, 'R');
	else
		return (0);
	render(fractol);
	return (0);
}

int	mouse_event(int keycode, int x, int y, t_fractol *fractol)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(fractol, 0.5);
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		if (x < 0)
			move(fractol, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move (fractol, (double)x / WIDTH, 'R');
		if (y < 0)
			move(fractol, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move(fractol, (double)y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(fractol, 2);
	else
		return (0);
	render(fractol);
	return (0);
}
