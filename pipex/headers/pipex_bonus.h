/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:07:40 by vmalassi          #+#    #+#             */
/*   Updated: 2023/09/07 11:14:02 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/headers/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

int		open_file(char *path, int open_type);
int		set_pipe(int pipex[2]);
char	*get_command_path(char *command, char **envp);
char	*get_options(char *cmd_and_options);
char	*get_command(char *cmd_and_options);
char	**get_cmd_options(char *tab[4], char *options, char *cmd, char *file);
void	close_pipe(int pipex[2]);
void	free_tab(char **tab);
void	last_command(int output_fd, char **argv, int argc, char **envp);
void	exec_command(char *command_and_options, char **envp);
#endif