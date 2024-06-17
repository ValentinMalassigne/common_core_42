/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:50 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:47:51 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "./graphics.h"
# include "./timer.h"
# include "main/options.h"
# include "canvas/canvas.h"
# include "camera/camera.h"
# include <stdbool.h>

/*
The engine handles:
	- the graphics subsystem (display, window, framebuffer)
	- the inputs (keyboard & structure events)
	- the timer (the timer is used for enforcing the window's FPS)
*/
typedef struct s_engine
{
	t_graphics		*grph;
	t_timer			*timer;
	float			timestep;
	bool			is_running;
}	t_engine;

// Initialize the engine's subsystems with the specified options.
int		engine_init(t_render *rd, t_options *opt, void *arena);

/* Loop the engine until the user terminates. The content of the window is
updated with the canvas every frame.*/
void	engine_run(t_render *rd, t_canvas *canvas, t_camera *camera);

/* To be called on termination. This function performs the cleanups for all
resources that won't be released by simply destroying the arena. */
void	engine_terminate(t_engine *eng);

/* Get engine state. */
bool	engine_is_running(t_engine *eng);

/* INTERNAL
================================================================================
*/
// Agregate because the callback used by mlx_loop_hook takes only one argument.
typedef struct s_loop_args
{
	t_engine	*eng;
	t_canvas	*canvas;
	t_camera	*camera;
}	t_loop_args;

#endif
