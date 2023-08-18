/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:24:20 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/20 17:40:53 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include <errno.h>
#include <string.h>

static void	exec_command(char *command_and_options, char **envp)
{
	char	**splited_command_options;
	char	*command_path;

	splited_command_options = ft_split(command_and_options, ' ');
	command_path = get_command_path(splited_command_options[0], envp);
	if (execve(command_path, splited_command_options, envp) == -1)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(splited_command_options[0], 2);
		free(command_path);
		free_tab(splited_command_options);
	}
}

pid_t	run_first_command(int pipex[2], char **argv, char **envp)
{
	pid_t	pid;
	int		input_fd;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		input_fd = open_file(argv[1], 0);
		dup2(input_fd, 0);
		dup2(pipex[1], 1);
		close_pipe(pipex);
		exec_command(argv[2], envp);
	}
	return (pid);
}

static void	run_second_command(int pipex[2], char **argv, char **envp)
{
	pid_t	pid;
	int		output_fd;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		output_fd = open_file(argv[4], 1);
		dup2(output_fd, 1);
		dup2(pipex[0], 0);
		close_pipe(pipex);
		exec_command(argv[3], envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipex[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
	{
		ft_printf("Error : Invalid number of arguments\n");
		return (-1);
	}
	if (set_pipe(pipex) == -1)
		return (-1);
	pid = run_first_command(pipex, argv, envp);
	if (pid > 0)
		waitpid(pid, &status, 0);
	run_second_command(pipex, argv, envp);
	return (0);
}
