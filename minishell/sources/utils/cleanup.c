/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:10:57 by vmalassi          #+#    #+#             */
/*   Updated: 2024/01/29 08:17:18 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* free_data:
 *	Frees all of the data used to run a command. If clear_history is true,
 *	frees the environment and the command history before returning.
 */
void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		lstclear_token(&data->token, &free_ptr);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (data && data->working_dir)
			free_ptr(data->working_dir);
		if (data && data->old_working_dir)
			free_ptr(data->old_working_dir);
		if (data && data->env)
			free_str_tab(data->env);
		rl_clear_history();
	}
}

/* close_fds:
 *	Closes opened file descriptors, including pipes and input and
 *	output fds. If close_backups is set to true, it also closes
 *	backup STDIN and STDOUT file descriptors.
 */
void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

/* free_io:
 *	Frees the input/output fd structure.
 */
void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

/* free_str_tab:
 *	Frees an array of strings.
 */
void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

/* free_ptr:
 *	Frees a pointer of any type if it is not NULL and sets it to NULL.
 *	This avoids accidental double-frees.
 */
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
