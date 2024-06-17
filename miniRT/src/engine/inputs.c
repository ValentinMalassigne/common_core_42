/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:11 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:12 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./engine.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

static void	loop_end(t_engine *eng)
{
	eng->is_running = false;
	mlx_loop_end(eng->grph->mlx_ptr);
}

static int	inputs_process_structure(t_engine *eng)
{
	loop_end(eng);
	return (0);
}

static int	inputs_process_keypress(int keycode, t_render *rd)
{
	t_camera	*camera;
	float		move_speed;

	camera = rd->camera;
	move_speed = 0.01f;
	if (keycode == XK_Escape)
		loop_end(rd->engine);
	if (keycode == XK_w)
		camera->center.y -= move_speed;
	if (keycode == XK_a)
		camera->center.x += move_speed;
	if (keycode == XK_s)
		camera->center.y += move_speed;
	if (keycode == XK_d)
		camera->center.x -= move_speed;
	return (0);
}

void	inputs_bind(t_render *rd)
{
	t_engine	*eng;

	eng = rd->engine;
	mlx_hook(eng->grph->win_ptr, DestroyNotify, StructureNotifyMask,
		inputs_process_structure, eng);
	mlx_hook(eng->grph->win_ptr, KeyPress, KeyPressMask,
		inputs_process_keypress, rd);
}
