/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:15:01 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/17 17:24:58 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static void	get_julia_settings(t_fractol *fractol, int argc, char **argv)
{
	if (fractol->set != 2 || argc == 2)
	{
		fractol->julia_r = 0.285;
		fractol->julia_i = 0.01;
		return ;
	}
	if (argc == 3)
		print_instructions(fractol);
	if (!ft_strchr(argv[2], '.'))
		print_instructions(fractol);
	if (!ft_strchr(argv[3], '.'))
		print_instructions(fractol);
	fractol->julia_r = ft_atof(argv[2]);
	fractol->julia_i = ft_atof(argv[3]);
	if (fractol->julia_r > 2.0 || fractol->julia_r < -2.0)
		print_instructions(fractol);
	if (fractol->julia_i >= 2.0 || fractol->julia_i <= -2.0)
		print_instructions(fractol);
}

static int	compare_arg(char *arg, char *str, char c, char number)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		arg[i] = ft_tolower(arg[i]);
		i++;
	}
	if (!ft_strncmp(arg, str, ft_strlen(str) + 1))
		return (1);
	else if (arg[1] == '\0' && (arg[0] == c || arg[0] == number))
		return (1);
	return (0);
}

static void	get_set(t_fractol *fractol, char **argv)
{
	if (compare_arg(argv[1], "mandelbrot", 'm', '1'))
		fractol->set = 1;
	else if (compare_arg(argv[1], "julia", 'j', '2'))
		fractol->set = 2;
	else
		print_instructions(fractol);
}

static void	pars_args(int argc, char **argv, t_fractol *fractol)
{
	get_set(fractol, argv);
	if (fractol->set != 2 && argc > 2)
		print_instructions(fractol);
	else if (fractol->set == 2 && argc > 4)
		print_instructions(fractol);
	get_julia_settings(fractol, argc, argv);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
		print_instructions(&fractol);
	init_struct(&fractol);
	pars_args(argc, argv, &fractol);
	init(&fractol);
	render(&fractol);
	print_controls();
	mlx_hook(fractol.win, EVENT_CLOSE_BTN, 0, end_fractol, &fractol);
	mlx_key_hook(fractol.win, key_event, &fractol);
	mlx_mouse_hook(fractol.win, mouse_event, &fractol);
	mlx_loop(fractol.mlx);
}
