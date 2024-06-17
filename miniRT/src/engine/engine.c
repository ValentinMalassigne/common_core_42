/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:45 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:47:46 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera/camera.h"
#include "engine.h"
#include "maths/maths.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdlib.h>

#define KEY_ESCAPE 65307
#define KEY_PRESS 2
#define KEY_RELEASE 3
#define KEY_EXIT 17
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_SPACE 32

void		inputs_bind(t_render *rd);

int	engine_init(t_render *rd, t_options *opt, void *arena)
{
	t_engine	*eng;

	eng = rd->engine;
	eng->grph = graphics_create(opt->window_width, opt->window_aspect, arena);
	if (!eng->grph)
		return (EXIT_FAILURE);
	eng->timer = rt_timer_create(arena);
	eng->timestep = 1e3f / opt->fps;
	inputs_bind(rd);
	eng->is_running = true;
	return (EXIT_SUCCESS);
}

static int	main_img(t_loop_args *args)
{
	t_engine	*eng;
	t_canvas	*canvas;
	static int	last_time = 0;
	int			time_to_wait;

	eng = args->eng;
	canvas = args->canvas;
	time_to_wait = eng->timestep - (timer_get_ticks(eng->timer) - last_time);
	if (time_to_wait > 0 && time_to_wait <= eng->timestep)
		timer_delay(time_to_wait);
	last_time = timer_get_ticks(eng->timer);
	graphics_clear(eng->grph);
	graphics_update_framebuffer(eng->grph, canvas);
	graphics_present(eng->grph);
	return (EXIT_SUCCESS);
}

void	engine_run(t_render *rd, t_canvas *canvas, t_camera *cam)
{
	t_loop_args	args;
	t_engine	*eng;

	args.eng = rd->engine;
	args.canvas = canvas;
	args.camera = cam;
	eng = rd->engine;
	main_img(&args);
	mlx_loop(eng->grph->mlx_ptr);
}

void	engine_terminate(t_engine *eng)
{
	graphics_destroy(eng->grph);
}

bool	engine_is_running(t_engine *eng)
{
	bool	ret;

	ret = eng->is_running;
	return (ret);
}
