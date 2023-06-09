/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:38:01 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 17:50:08 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
#include "libft.h"

int		hex_len(unsigned long decimal);
int		ft_printf(const char *format, ...);
int		print_char(char c);
int		print_str(char *str);
int		print_ptr(void *ptr);
int		print_deci(int d);
int		print_unsigned(unsigned int nbr);
int		print_hex(unsigned int decimal, int upper);
int		unsigned_int_length(unsigned int nbr);
int		int_length(int nbr);
void	put_hex(unsigned long decimal, int upper);
void	put_unsigned(unsigned int n, int fd);

#endif