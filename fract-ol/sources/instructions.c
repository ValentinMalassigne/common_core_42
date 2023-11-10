/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:25:10 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/10 20:45:04 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	print_instructions(t_fractol *fractol)
{
	ft_printf("Fractol program parameters :\n\n");
	ft_printf("Choose between Mandelbrot and Julia\n");
	ft_printf("- For Mandelbrot write M or 1 or Mandelbrot\n");
	ft_printf("- For Julia write J or 2 or Julia\n\n");
	ft_printf("For example run : ./fractol M\n\n");
	ft_printf("Julia settings :\n");
	ft_printf("Your can add settings to Julia fractal :\n");
	ft_printf("Settins must be in the form of a decimal number");
	ft_printf(" between -2.0 and 2.0.\n");
	ft_printf("For example run : ./fractol J 1.5141 -0.8651\n");
	exit_and_free(1, fractol);
}

void	print_controls(void)
{
	ft_printf("Controls :\n");
	ft_printf("Use mouse scroll to zoom in or zoom out\n");
	ft_printf("Use arrow keys to moove, up, down, left or right\n");
	ft_printf("Press ESC to quit\n");
}
