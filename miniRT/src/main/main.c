/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:26 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:27 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/engine.h"
#include "canvas/canvas.h"
#include "camera/camera.h"
#include "errors/errors.h"
#include "./options.h"
#include "libft.h"
#include "parsing/parsing.h"
#include <stdio.h>
#include <stdlib.h>

void	options_init(t_options *opt)
{
	opt->window_width = WIN_WIDTH;
	opt->window_aspect = WIN_ASPECT;
	opt->fps = FPS;
}

void	run(t_render *rd)
{
	camera_render(rd);
	engine_run(rd, rd->canvas, rd->objects->camera);
	engine_terminate(rd->engine);
	canvas_destroy(rd->canvas);
}

int	main(int argc, char *argv[])
{
	void		*arena;
	t_objects	*objects;
	t_options	options;
	t_render	*rd;

	if (argc != 2)
		exit_error("\nusage: ./miniRT path/to/file.rt\n\n");
	arena = arena_init((size_t)1e8);
	if (!arena)
		exit_error("Error: insufficient memory\n");
	options_init(&options);
	objects = init_objects(arena, argv);
	rd = &(t_render){.camera = objects->camera,
		.canvas = canvas_create(options.window_width,
			options.window_aspect, arena),
		.engine = arena_alloc(arena, sizeof(t_engine)),
		.objects = objects, .arena = arena};
	if (engine_init(rd, &options, arena) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	camera_init_viewport(objects->camera, rd->canvas->width,
		rd->canvas->height, arena);
	run(rd);
	arena_destroy(arena);
	return (EXIT_SUCCESS);
}
