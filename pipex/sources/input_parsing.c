/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:31:40 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/18 21:02:53 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

char	**get_path_list(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			return ft_split(envp[i], ':');
		}
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *command, char **envp)
{
	int		i;
	char	**path_list;
	char	*command_path;
	char	*command_with_slash;

	path_list = get_path_list(envp);
	command_path = NULL;

	i = 0;
	while (path_list[i])
	{
		command_with_slash = ft_strjoin("/", command);
		command_path = ft_strjoin(path_list[i], command_with_slash);
		free(command_with_slash);
		if (access(command_path, X_OK) == 0)
			break;
		i++;
		free(command_path);
	}
	i = 0;
	while (path_list[i])
		free(path_list[i++]);
	free(path_list);
	return (command_path);
}

char	*get_options(char *cmd_and_options)
{
	char	*options;
	int		i;

	if (!cmd_and_options)
		return (NULL);
	i = 0;
	while (*cmd_and_options && *cmd_and_options != ' ')
		cmd_and_options++;
	while (cmd_and_options[i] && cmd_and_options[i] != ' ')
		i++;
	if (i == 0)
		return (NULL);
	options = malloc((i +1) * sizeof(char));
	i = 0;
	while (cmd_and_options[i] && cmd_and_options[i] != ' ')
	{
		options[i] = cmd_and_options[i];
		i++;
	}
	options[i] = 0;
	return (options);
}

char	*get_command(char *cmd_and_options)
{
	char	*command;
	int		i;

	if (!cmd_and_options)
		return (NULL);
	i = 0;
	while (cmd_and_options[i] && cmd_and_options[i] != ' ')
		i++;
	if (i == 0)
		return (NULL);
	command = malloc((i + 1) * sizeof(char));
	i = 0;
	while (cmd_and_options[i] && cmd_and_options[i] != ' ')
	{
		command[i] = cmd_and_options[i];
		i++;
	}
	command[i] = 0;
	return (command);
}

char	**get_cmd_options(char *tab[4], char *options, char *cmd, char *file)
{
	tab[0] = cmd;

	if (options)
	{
		tab[1] = options;
		tab[2] = ft_strdup(file);
	}
	else
	{
		tab[1] = ft_strdup(file);
		tab[2] = NULL;
	}
	tab[3] = NULL;
	return (tab);
}
