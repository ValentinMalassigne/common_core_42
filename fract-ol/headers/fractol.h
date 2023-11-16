/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:08:48 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/16 18:37:22 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../libft/headers/libft.h"
# include "values.h"
# include <stdio.h>
# include <math.h>

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	julia_r;
	double	julia_i;
	int		color;
	int		*colors;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
}	t_fractol;

void	print_instructions(t_fractol *f);
void	print_controls(void);
void	exit_and_free(int value, t_fractol *fractol);
void	init_struct(t_fractol *fractol);
double	ft_atof(char *str);
void	init(t_fractol *fractol);
void	set_color_waves(t_fractol *fractol, int color);
void	render(t_fractol *fractol);
int		end_fractol(t_fractol *mlx);
int		key_event(int keycode, t_fractol *fractol);
int		mouse_event(int keycode, int x, int y, t_fractol *fractol);
int		mandelbrot(double pr, double pi);
int		julia(t_fractol *fractol, double r, double i);

#endif