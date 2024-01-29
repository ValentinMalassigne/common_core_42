/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:55:54 by vmalassi          #+#    #+#             */
/*   Updated: 2024/01/29 07:54:34 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* env_builtin:
*	Executes the builtin env command: Prints the environment variables.
*/
int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
