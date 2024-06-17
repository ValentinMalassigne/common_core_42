/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:28:23 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/30 14:32:08 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "color/color.h"
# include "errors/errors.h"
# include "libft.h"
# include "maths/maths.h"
# include "objects/objects.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 32

typedef struct s_ambient
{
	float		ratio;
	t_color		color;
}				t_ambient;

typedef struct s_light
{
	t_point3	origin;
	float		ratio;
	t_color		color;
}				t_light;

/* GET NEXT LINE FUNCTIONS */
int				ft_check_line(char *dest);
int				ft_strlen_line(char *dest);
char			*ft_join_line(t_arena *arena, char *src, char *buff);
void			ft_cute_line(char *dest);
char			*get_next_line(t_arena *arena, int fd);

/* LIST FUNCTIONS */
t_list			*ft_lstnew(t_arena *arena, void *data);
void			ft_lstadd_back(t_list **alst, t_list *new);

/* PARSING FUNCTIONS */
t_list			*parsing_to_list(t_arena *arena, char *file);
t_list			*token_to_list(t_arena *arena, char *line);
t_ambient		*find_ambient(t_arena *arena, t_list *list, char *str);
t_light			*find_light(t_arena *arena, t_list *list, char *str);
t_list			*find_spheres(t_arena *arena, t_list *list_params);
t_list			*find_planes(t_arena *arena, t_list *list_params);
t_list			*find_cylinders(t_arena *arena, t_list *list_params);
t_list			*find_id_line(t_list *list, char *str);
t_list			*list_all(t_list *sp, t_list *pl, t_list *cyl, t_arena *arena);
t_object		*convert_cyl_to_obj(t_arena *arena, t_cylinder *cylinder);
t_object		*convert_pln_to_obj(t_arena *arena, t_plane *plane);
t_object		*convert_sph_to_obj(t_arena *arena, t_sphere *sphere);
/* UTILS FUNCTIONS */
void			check_duplicated_capitals(t_arena *arena, t_list *params);
char			*str_is_float(t_arena *arena, char *str, char *msg);
int				float_in_range(float value, float min, float max);
int				is_rgb(char *str);
t_vec3			extract_rgb(t_arena *arena, char *str, char *msg);
int				is_coordinates(char *str);
#endif // !PARSING_H