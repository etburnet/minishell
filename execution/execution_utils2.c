/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:40:34 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/24 17:48:05 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_child(t_data *data, int cmd, int fdin, int fdout)
{
	if (dup2(fdin, 0) == -1 || dup2(fdout, data->append_id) == -1)
		return (perror("dup2"), 1);
	close_all(data, fdin, fdout, cmd);
	init_signal_handler(data, 5);
	clear_history();
	if (execve(data->token[cmd].full_path, data->token[cmd].tab, data->cp_env) == -1)
		put_error(ERR_CMD, data->token[cmd].tab[0]);
	if(errno == EACCES)
		return (27);
	return (2);
}

void	manage_files(t_data *data, t_token tok_i, t_token *tok_cmd, int *cmd)
{
	int	fd;
	
	fd = -2;
	//printf("manage file %s, cmd %d\n", tok_i.tab[0], *cmd);
	if (*cmd == -1)
	{
		if (tok_i.type == infile)
			fd = open_file(data, tok_i, 0, *cmd);
		else if (tok_i.type == outfile)
			fd = open_file(data, tok_i, 1, *cmd);
		else if (tok_i.type == append_out)
			fd = open_file(data, tok_i, 5, *cmd);
		if (fd == -1)
			*cmd = -2;
		ft_close(data, fd, -1, -1);
		return ;
	}
	if (tok_i.type == infile)
	{
		if(tok_cmd->fdin != -1 && tok_cmd->fdin != 0)
			close(tok_cmd->fdin);
		tok_cmd->fdin = open_file(data, tok_i, 0, *cmd);
	}
	else if (tok_i.type == outfile)
	{
		if(tok_cmd->fdout != -1 && tok_cmd->fdout != 1)
			close(tok_cmd->fdout);
		tok_cmd->fdout = open_file(data, tok_i, 1, *cmd);
	}
	else if (tok_i.type == append_out)
	{
		if(tok_cmd->fdout != -1 && tok_cmd->fdout != 1)
			close(tok_cmd->fdout);
		tok_cmd->fdout = open_file(data, tok_i, 5, *cmd);;
	}
	else if (tok_i.type == append_id)
		data->append_id = ft_atoi(tok_i.tab[0]);
	else if(tok_i.type == here_doc)
	{
		if(tok_cmd->fdin != -1 && tok_cmd->fdin != 0)
			close(tok_cmd->fdin);
		tok_cmd->fdin = open_file(data, tok_i, 4, *cmd);
	}
}

int	manage_pipe(t_data *data, t_token *tok)
{
	//printf("ofd0 %d, ofd1 %d\n", data->old_pipe[0], data->old_pipe[1]);
	if (pipe(data->pipe_fd) == -1)
		return (perror("pipe"), 1);
	if (tok->first != 1 && tok->fdin == 0 && data->old_pipe[0] > -1)
		tok->fdin = data->old_pipe[0];
	else if (tok->first != 1 && data->old_pipe[0] > -1 )
		close(data->pipe_fd[0]);
	data->old_pipe[0] = data->pipe_fd[0];
	if (tok->last != 1 && tok->fdout == 1)
		tok->fdout = data->pipe_fd[1];
	else
		close(data->pipe_fd[1]);
	data->old_pipe[1] = data->pipe_fd[1];
	//printf("fd0 %d, fd1 %d\n", data->pipe_fd[0], data->pipe_fd[1]);
	return (0);
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

int	ft_check_entry(t_data *data, int cmd, int fdin, int fdout)
{
	int		fd;
	
	if (ft_strncmp(data->token[cmd].tab[0], "./", 2) == 0 || data->token[cmd].tab[0][0] == '/')
	{
		fd = open(data->token[cmd].tab[0], O_WRONLY);
		if (errno == EISDIR)
			return (ft_close(data, fdin, fdout, cmd),
				perror(data->token[cmd].tab[0]), 126);
		if (fd >= 0)
			close(fd);
		fd = access(data->token[cmd].tab[0], X_OK);
		if (fd != 0 && errno == EACCES)
			return (ft_close(data, fdin, fdout, cmd),
				perror(data->token[cmd].tab[0]), 126);
	}
	if (!data->token[cmd].full_path)
		return (put_error(ERR_CMD, data->token[cmd].tab[0]), ft_close(data,
				fdin, fdout, cmd), 127);
	return (0);
}
