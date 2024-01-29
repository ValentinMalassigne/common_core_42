/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 08:48:52 by vmalassi          #+#    #+#             */
/*   Updated: 2024/01/29 08:28:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_last_exit_code;

static bool	start_check(t_data *data, int ac, char **av)
{
	if (ac != 1 && ac != 3)
		return (usage_message(false));
	if (ac == 3)
	{
		data->interactive = false;
		if (!av[1] || (av[1] && ft_strcmp(av[1], "-c") != 0))
			return (usage_message(false));
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (usage_message(false));
	}
	else
		data->interactive = true;
	return (true);
}

void	minishell_interactive(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->user_input = readline(PROMPT);
		set_signals_noninteractive();
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 1;
		free_data(data, false);
	}
}

/* minishell_noninteractive:
 *	Runs parsing and execution in noninteractive mode, i.e. when
 *	minishell is started with the -c option followed by an argument
 *	containing the commands to be executed:
 *		./minishell -c "echo hello | wc -c"
 *	Commands in this mode can be separated by a semicolon, ';' to
 *	indicate sequential execution:
 *		./minishell -c "echo hello; ls"
 *	-> echo hello is the first command run
 *	-> ls is the second
 */
void	minishell_noninteractive(t_data *data, char *arg)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(arg, ';');
	if (!user_inputs)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	while (user_inputs[i])
	{
		data->user_input = ft_strdup(user_inputs[i]);
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 1;
		i++;
		free_data(data, false);
	}
	free_str_tab(user_inputs);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(&data, argc, argv) || !init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	if (data.interactive)
		minishell_interactive(&data);
	else
		minishell_noninteractive(&data, argv[2]);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
