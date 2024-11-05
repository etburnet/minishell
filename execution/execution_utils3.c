/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:20:20 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/05 16:04:39 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	catch_cmd(t_data *data, int i)
{
	while (i < data->lenght_token && data->token[i].type != pipes)
	{
		if (data->token[i].type == command || data->token[i].type == built_in
			|| data->token[i].type == variable)
			return (i);
		i++;
	}
	return (-1);
}

void	close_all(t_data *data, int fdin, int fdout, int cmd)
{
	ft_close(data, fdin, fdout, cmd);
	ft_close(data, data->pipe_fd[0], data->pipe_fd[1], -1);
	ft_close(data, data->old_pipe[0], data->old_pipe[1], -1);
}

int	ft_check_file(t_token tok)
{
	if (tok.type != pipes)
		if (tok.type != infile)
			if (tok.type != outfile)
				if (tok.type != append)
					return (0);
	return (1);
}

int	ft_check_fd(t_data *data, int *i, int *cmd)
{
	if (*cmd >= 0 && *i < data->lenght_token && (data->token[*cmd].fdin == -1
			|| data->token[*cmd].fdout == -1))
	{
		while (*i < data->lenght_token && data->token[*i].type != pipes)
			(*i)++;
		if (*i == data->lenght_token)
			return (-1);
		if (data->token[*i].type == pipes)
			return (*cmd);
		if (data->token[*i].last == 1)
			close_all(data, -1, -1, *cmd);
	}
	return (-2);
}

int	command_return(t_data *data, t_token tok, int ret)
{
	if (ret != 2 && ret != 127 && ret != 126 && ret != 0)
	{
		ft_close(data, tok.fdin, tok.fdout, -1);
		data->status = ret % 255;
		return (ret);
	}
	ft_close(data, tok.fdin, tok.fdout, -1);
	return (0);
}
