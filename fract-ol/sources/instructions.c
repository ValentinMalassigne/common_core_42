/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:25:10 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 15:29:44 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void print_instructions(t_fractol *fractol)
{
	ft_printf("TODO instructions\n");
	exit_and_free(1,fractol);
}

void	print_controls()
{
	ft_printf("Controls :\n");
	ft_printf("Use mouse scroll to zoom in or zoom out\n");
	ft_printf("Use arrow keys to moove, up, down, left or right\n");
	ft_printf("Press ESC to quit\n");
}