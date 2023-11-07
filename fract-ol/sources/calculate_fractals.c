/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fractals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:39:30 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 15:36:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

int	mandelbrot(double pr, double pi)
{
	int		n;
	double	r;
	double	i;
	double	temp;

	r = 0;
	i = 0;
	n = 0;
	while (n < ITERATIONS_LIMIT)
	{
		if ((r * r + i * i) > 4.0)
			break;
		temp = 2 * r * i + pi;
		r = r * r - i * i + pr;
		i = temp;
		n++;
	}
	return (n);
}

int	julia(t_fractol *fractol, double r, double i)
{
	int n;
	double temp;

	n = 0;
	while (n < ITERATIONS_LIMIT)
	{
		if ((i * i + r * r) > 4.0)
			break ;
		temp = 2 * r * i + fractol->julia_i;
		r = r * r - i * i + fractol->julia_r;
		i = temp;
		n++;
	}
	return (n);
}
