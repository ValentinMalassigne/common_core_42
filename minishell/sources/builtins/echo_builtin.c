/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:06:28 by vmalassi          #+#    #+#             */
/*   Updated: 2024/01/29 08:27:54 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* is_n_flag:
*	Checks whether an arg is an -n option flag.
*	Returns true if the arg is some variation of -n, -nnnn, -nn, etc.
*	Returns false if it contains anything other than
*	- and n (ex. --n -nnnm -n1234)
*/
static bool	is_n_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
}

/* echo_print_args:
*	Prints the given array of aruments to STDOUT.
*/
static void	echo_print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/* echo_builtin:
*	Executes the echo builtin command: prints the given strings
*	and adds a \n character or not depending on the -n option.
*	Returns 1 on completion.
*/
int	echo_builtin(t_data *data, char **args)
{
	int		i;
	bool	n_flag;

	(void)data;
	n_flag = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
