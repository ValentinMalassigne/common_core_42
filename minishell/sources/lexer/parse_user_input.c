/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:55:08 by vmalassi          #+#    #+#             */
/*   Updated: 2024/01/29 08:22:23 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_user_input(t_data *data)
{
	if (data->user_input == NULL)
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
	add_history(data->user_input);
	if (tokenization(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (check_if_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	create_commands(data, data->token);
	return (true);
}
