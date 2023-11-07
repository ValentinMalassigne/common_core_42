/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:29:06 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 15:23:12 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void exit_and_free(int code, t_fractol *fractol)
{
	if (!fractol)
		exit(code);
	if (fractol->colors)
		free(fractol->colors);
	if (fractol->img)
		mlx_destroy_image(fractol->mlx, fractol->img);
	if (fractol->win && fractol->mlx)
		mlx_destroy_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_loop_end(fractol->mlx);
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit(code);
}

static int ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (c);
	return (0);
}

static int skip_spaces_get_sign(char *str, int *sign)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

double	ft_atof(char *str)
{
	int		i;
	double	res;
	int		sign;
	double	fractional;

	res = 0;
	fractional = 0.1;
	sign = 1;
	i = skip_spaces_get_sign(str, &sign);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
		res = res * 10 + str[i++] - '0';
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res + (str[i] - '0') * fractional;
		fractional *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-999);
	return (res * sign);
}

int	end_fractol(t_fractol *mlx)
{
	exit_and_free(0, mlx);
	return (0);
}