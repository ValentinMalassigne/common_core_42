/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:13:04 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/10 20:46:59 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	init_struct(t_fractol *fractol)
{
	fractol->mlx = NULL;
	fractol->win = NULL;
	fractol->img = NULL;
	fractol->data = NULL;
	fractol->set = -1;
	fractol->min_r = 0;
	fractol->max_r = 0;
	fractol->min_i = 0;
	fractol->max_i = 0;
	fractol->julia_r = 0;
	fractol->julia_i = 0;
	fractol->colors = NULL;
	fractol->color = (0 << 16) + (100 << 8) + (255);
	fractol->pixel_bits = -1;
	fractol->line_bytes = -1;
	fractol->endian = -1;
}

static void	init_image(t_fractol *fractol)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;

	fractol->colors = ft_calloc((ITERATIONS_LIMIT + 1), sizeof(int));
	if (!(fractol->colors))
	{
		ft_putendl_fd("Fractol: error on colors calloc", 2);
		exit_and_free(1, fractol);
	}
	fractol->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!(fractol->img))
	{
		ft_putendl_fd("MLX: error when creating new image", 2);
		exit_and_free(1, fractol);
	}
	fractol->data = mlx_get_data_addr(fractol->img, &pixel_bits,
			&line_bytes, &endian);
	fractol->pixel_bits = pixel_bits;
	fractol->line_bytes = line_bytes;
	fractol->endian = endian;
}

static void	set_up_coordinate_axes(t_fractol *fractol)
{
	if (fractol->set == 2)
	{
		fractol->min_r = -2.0;
		fractol->max_r = 2.0;
		fractol->min_i = -2.0;
		fractol->max_i = fractol->min_i + (fractol->max_r - fractol->min_r)
			* HEIGHT / WIDTH;
	}
	else
	{
		fractol->min_r = -2.0;
		fractol->max_r = 1.0;
		fractol->max_i = -1.5;
		fractol->min_i = fractol->max_i + (fractol->max_r - fractol->min_r)
			* HEIGHT / WIDTH;
	}
}

void	init(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
	{
		ft_putendl_fd("MLX: error on mlx initialization", 2);
		exit_and_free(1, fractol);
	}
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fractol");
	if (!fractol->win)
	{
		ft_putendl_fd("MLX: error on creating new window", 2);
		exit_and_free(1, fractol);
	}
	set_up_coordinate_axes(fractol);
	init_image(fractol);
	set_color_waves(fractol, fractol->color);
}
