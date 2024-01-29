/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:10:23 by vmalassi          #+#    #+#             */
/*   Updated: 2024/01/29 08:10:24 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parse_pipe(t_command **cmd, t_token **token_lst)
{
	t_command	*last_cmd;

	last_cmd = lst_last_cmd(*cmd);
	last_cmd->pipe_output = true;
	lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
	*token_lst = (*token_lst)->next;
}
