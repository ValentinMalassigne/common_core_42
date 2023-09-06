/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:24:20 by vmalassi          #+#    #+#             */
/*   Updated: 2023/09/06 17:38:54 by vmalassi         ###   ########.fr       */
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

void	redirect_here_doc(char **argv, int pipex[2])
{
	char	*input;

	close(pipex[0]);
	while (1)
	{
		input = get_next_line(0);
		if (ft_strncmp(input, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(input);
			exit(0);
		}
		ft_putstr_fd(input, pipex[1]);
		free(input);
	}
}

void	manage_here_doc(char **argv)
{
	int		pipex[2];
	int		status;
	pid_t	pid;

	if (set_pipe(pipex) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		redirect_here_doc(argv, pipex);
	else
	{
		close(pipex[1]);
		dup2(pipex[0], 0);
		waitpid(pid, &status, 0);
	}
}

void	exec_pipex(char *command, char **envp)
{
	int		pipex[2];
	int		status;
	pid_t	pid;

	if (set_pipe(pipex) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
	{
		close(pipex[0]);
		dup2(pipex[1], 1);
		exec_command(command, envp);
	}
	else
	{
		close(pipex[1]);
		dup2(pipex[0], 0);
		waitpid(pid, &status, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	start_index;
	int	input_fd;
	int	output_fd;

	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
	{
		ft_printf("Error : Invalid number of arguments\n");
		return (-1);
	}
	else if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		start_index = 3;
		manage_here_doc(argv);
	}
	else
	{
		input_fd = open_file(argv[1], 0);
		dup2(input_fd, 0);
		start_index = 2;
	}
	output_fd = open_file(argv[argc - 1], start_index - 1);
	while (start_index < argc - 2)
		exec_pipex(argv[start_index++], envp);
	dup2(output_fd, 1);
	exec_command(argv[argc - 2], envp);
}
