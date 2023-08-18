/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:07:40 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/20 17:42:04 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/headers/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

int     open_file(char *path, int open_type);
int		set_pipe(int pipex[2]);
char	*get_command_path(char *command, char **envp);
char	*get_options(char *cmd_and_options);
char	*get_command(char *cmd_and_options);
char	**get_cmd_options(char *tab[4], char *options, char *cmd, char *file);
void	cmd_on_file(char *cmd_tab, char *file, int *out_pipe, char **env);
void	cmd_on_string(char *cmd_tab, int *in_pipe, int *out_pipe, char **env);
void	close_pipe(int pipex[2]);
void	free_tab(char **tab);
#endif