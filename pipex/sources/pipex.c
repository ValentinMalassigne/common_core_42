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

int	write_outfile(char	*file_name, char	*cmd_output)
{
	int	outfile;

	outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_printf("Error when open / create / truncate file\n");
		return (-1);
	}
	write(outfile, cmd_output, ft_strlen(cmd_output));
	free(cmd_output);
	return (0);
}

int	run_cat_cmd(char cmd_output[4096], char **argv, char **envp)
{
	int		out_pipe[2];
	char	*cat_cmd;

	cat_cmd = malloc(5 * sizeof (char));
	cat_cmd = ft_memset(cat_cmd, 0, 5);
	cat_cmd[0] = 'c';
	cat_cmd[1] = 'a';
	cat_cmd[2] = 't';
	ft_memset(cmd_output, 0, 4096);
	if (set_pipe(out_pipe) == -1)
		return (-1);
	cmd_on_file(cat_cmd, argv[1], out_pipe, envp);
	read(out_pipe[0], cmd_output, 4096);
	close_pipe(out_pipe);
	free(cat_cmd);
	return (0);
}

int	run_cmd(char cmd_output[4096], char *cmd, char **envp)
{
	int	in_pipe[2];
	int	out_pipe[2];

	if (set_pipe(in_pipe) == -1)
		return (-1);
	if (set_pipe(out_pipe) == -1)
		return (-1);
	write(in_pipe[1], cmd_output, ft_strlen(cmd_output));
	close(in_pipe[1]);
	cmd_on_string(cmd, in_pipe, out_pipe, envp);
	close(in_pipe[0]);
	ft_memset(cmd_output, 0, 4096);
	read(out_pipe[0], cmd_output, 4096);
	close_pipe(out_pipe);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char			*cmd_output;

	if (argc != 5)
	{
		ft_printf("Error : Invalid number of arguments\n");
		return (-1);
	}
	cmd_output = malloc(4096 * sizeof(char));
	if (!cmd_output)
	{
		ft_printf("Error : can't malloc output");
		return (-1);
	}
	if (run_cat_cmd(cmd_output, argv, envp) == -1)
		return (-1);
	if (run_cmd(cmd_output, argv[2], envp) == -1)
		return (-1);
	if (run_cmd(cmd_output, argv[3], envp) == -1)
		return (-1);
	return (write_outfile(argv[4], cmd_output));
}
