/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:36:48 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:44:40 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "src/arena/arena_internal.h"
# include <stdint.h>
# include <stdlib.h>

/*	list
==============
*/
struct	s_list;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;

}					t_list;

int		ft_lstsize(t_list *lst);

/*	c lib
==============
*/
size_t	ft_strlen(const char *s);
float	ft_atof(char *str);
long	ft_atol(const char *nptr);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strdup(t_arena *arena, const char *s);
char	*ft_itoa(int n);
char	*ft_strrev(char *str);
char	*ft_strtok(char *str, const char *delim);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);

/*	arena allocator
==============
*/
void	arena_reset(t_arena *arena);
void	arena_memset_temp(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t size);
void	*arena_init(size_t buffer_size);
void	arena_destroy(t_arena *arena);
#endif
