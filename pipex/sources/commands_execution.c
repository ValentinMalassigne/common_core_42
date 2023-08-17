/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:22:05 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/20 18:23:15 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	ex_on_file(char *cmd_path, char **options, int *pipe, char **env)
{
	pid_t	pid;
	int		i;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(pipe[0]);
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
		execve(cmd_path, options, env);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	i = 0;
	while (options[i])
		free(options[i++]);
}

static void	ex_on_str(char *cmd_path, char **options, int *pipes[2], char **env)
{
	pid_t	pid;
	int		*in_pipe;
	int		*out_pipe;
	int		i;
	int		status;

	in_pipe = pipes[0];
	out_pipe = pipes[1];
	pid = fork();
	if (pid == 0)
	{
		close(in_pipe[1]);
		close(out_pipe[0]);
		dup2(out_pipe[1], STDOUT_FILENO);
		dup2(in_pipe[0], STDIN_FILENO);
		close(out_pipe[1]);
		close(in_pipe[0]);
		execve(cmd_path, options, env);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	i = 0;
	while (options[i])
		free(options[i++]);
}

void	cmd_on_file(char *cmd_tab, char *file, int *out_pipe, char **env)
{
	char	*command;
	char	*options;
	char	*command_options[4];
	char	*command_path;

	if (access(file, R_OK) != 0)
	{
		ft_printf("Todo implement infile error\n");
		return ;
	}
	command = get_command(cmd_tab);
	if (!command)
	{
		ft_printf("TODO implement cmd = NULL\n");
		return ;
	}
	options = get_options(cmd_tab);
	get_cmd_options(command_options, options, command, file);
	command_path = get_command_path(command, env);
	if (!command_path)
	{
		ft_printf("Todo implement command_path error\n");
		return ;
	}
	ex_on_file(command_path, command_options, out_pipe, env);
}

void	cmd_on_string(char *cmd_tab, int *in_pipe, int *out_pipe, char **env)
{
	char	*command;
	char	*options;
	char	*command_options[3];
	char	*command_path;
	int		*pipes[2];

	command = get_command(cmd_tab);
	options = get_options(cmd_tab);
	command_options[0] = command;
	if (options)
		command_options[1] = options;
	else
		command_options[1] = NULL;
	command_options[2] = NULL;
	command_path = get_command_path(command, env);
	pipes[0] = in_pipe;
	pipes[1] = out_pipe;
	ex_on_str(command_path, command_options, pipes, env);
}
