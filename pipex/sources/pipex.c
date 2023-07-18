/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:24:20 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/18 18:51:33 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int				in_pipe[2];
	int				out_pipe[2];
	char			cmd_output[4090];
	unsigned long	i;

	if (argc != 4)
	{
		ft_printf("Error : Invalid number of arguments\n");
		return (-1);
	}
	i = 0;
	while (i < sizeof(cmd_output))
		cmd_output[i++] = 0;
	if (pipe(out_pipe) == -1)
	{
		ft_printf("TODO pipe creation failure\n");
		return (-1);
	}
	cmd_on_file(argv[2], argv[1], out_pipe, envp);
	read(out_pipe[0], cmd_output, sizeof(cmd_output));
	if (pipe(in_pipe) == -1)
	{
		ft_printf("TODO pipe creation failure\n");
		return (-1);
	}
	close(out_pipe[0]);
	close(out_pipe[1]);
	if (pipe(out_pipe) == -1)
	{
		ft_printf("TODO pipe creation failure\n");
		return (-1);
	}
	write(in_pipe[1], cmd_output, sizeof(cmd_output));
	close(in_pipe[1]);
	cmd_on_string(argv[3], in_pipe, out_pipe, envp);
	close(in_pipe[0]);
	i = 0;
	while (i < sizeof(cmd_output))
		cmd_output[i++] = 0;
	read(out_pipe[0], cmd_output, sizeof(cmd_output));
	close(out_pipe[0]);
	close(out_pipe[1]);
	ft_printf("Output:%s", cmd_output);
	return (0);
}
