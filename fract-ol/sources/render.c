/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:24:17 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/17 17:54:55 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static int	get_endian(void)
{
	int	a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		return (1);
	else
		return (0);
}

static void	set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	char	*ptr;
	int		dec;
	int		opp;

	opp = fractol->pixel_bits / 8;
	ptr = fractol->data + y * fractol->line_bytes;
	dec = opp;
	while (dec--)
	{
		if (get_endian() == fractol->endian)
		{
			if (get_endian())
				*(ptr + x * opp + dec) = ((char *)(&color))[4 - opp + dec];
			else
				*(ptr + x * opp + dec) = ((unsigned char *)(&color))[dec];
		}
		else
		{
			if (get_endian())
				*(ptr + x * opp + dec) = ((char *)(&color))[opp - 1 - dec];
			else
				*(ptr + x * opp + dec) = ((unsigned char *)(&color))[3 - dec];
		}
	}
}

static int	calculate_fractal(t_fractol *fractol, double pr, double pi)
{
	int	iterations;

	if (fractol->set == 1)
		iterations = mandelbrot(pr, pi);
	else
		iterations = julia(fractol, pr, pi);
	return (iterations);
}

void	render(t_fractol *fractol)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		iterations;

	mlx_clear_window(fractol->mlx, fractol->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = fractol->min_r + (double)x * (fractol->max_r - fractol->min_r)
				/ WIDTH;
			pi = fractol->max_i + (double)y * (fractol->min_i - fractol->max_i)
				/ HEIGHT;
			iterations = calculate_fractal(fractol, pr, pi);
			set_pixel_color(fractol, x, y,
				mlx_get_color_value(fractol->mlx, fractol->colors[iterations]));
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
