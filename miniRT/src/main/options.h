/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:30 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:32 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# define WIN_WIDTH	1600
# define WIN_ASPECT	1.777778f
# define FPS 10

typedef struct s_options
{
	int		window_width;
	float	window_aspect;
	float	fps;
}	t_options;

#endif
