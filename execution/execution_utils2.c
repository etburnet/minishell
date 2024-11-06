/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:40:34 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/06 11:42:47 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_child(t_data *data, int cmd, int fdin, int fdout)
{
	char	*full_p;

	if (data->token[cmd].full_path == NULL)
		full_p = "\0";
	else
		full_p = data->token[cmd].full_path;
	signal(SIGINT, ft_child_signal);
	signal(SIGQUIT, SIG_DFL);
	if (dup2(fdin, 0) == -1)
		return (perror("dup2 fdin"), 1);
	if (dup2(fdout, data->append_id) == -1)
		return (perror("dup2 fdout"), 1);
	close_all(data, fdin, fdout, cmd);
	clear_history();
	execve(full_p, data->token[cmd].tab, data->cp_env);
	if (errno == EFAULT || errno == ENOENT)
		return (put_error(ERR_CMD, data->token[cmd].tab[0]), 127);
	if (errno == EACCES)
		return (127);
	return (2);
}

void	open_redir(t_data *data, t_token tok_i, t_token *tok_cmd, int *cmd)
{
	if (tok_i.type == outfile || tok_i.type == append_out)
	{
		if (tok_cmd->fdout != -1 && tok_cmd->fdout != 1)
			close(tok_cmd->fdout);
		if (tok_i.type == outfile)
			tok_cmd->fdout = open_file(data, tok_i, 1, *cmd);
		else if (tok_i.type == append_out)
			tok_cmd->fdout = open_file(data, tok_i, 5, *cmd);
	}
	else if (tok_i.type == append_id)
		data->append_id = ft_atoi(tok_i.tab[0]);
	else if (tok_i.type == infile || tok_i.type == here_doc)
	{
		if (tok_cmd->fdin != -1 && tok_cmd->fdin != 0)
			close(tok_cmd->fdin);
		if (tok_i.type == infile)
			tok_cmd->fdin = open_file(data, tok_i, 0, *cmd);
		else if (tok_i.type == here_doc)
			tok_cmd->fdin = open_file(data, tok_i, 4, *cmd);
	}
}

void	manage_files(t_data *data, t_token tok_i, t_token *tok_cmd, int *cmd)
{
	int	fd;

	fd = -2;
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
	open_redir(data, tok_i, tok_cmd, cmd);
}

int	manage_pipe(t_data *data, t_token *tok)
{
	if (pipe(data->pipe_fd) == -1)
		return (perror("pipe"), 1);
	if (tok->first != 1 && tok->fdin == 0 && data->old_pipe[0] > -1)
		tok->fdin = data->old_pipe[0];
	else if (tok->fdin > 0 && data->old_pipe[0] > -1)
		close(data->old_pipe[0]);
	data->old_pipe[0] = data->pipe_fd[0];
	if (tok->last != 1 && tok->fdout == 1)
		tok->fdout = data->pipe_fd[1];
	else
		close(data->pipe_fd[1]);
	data->old_pipe[1] = data->pipe_fd[1];
	return (0);
}

int	ft_check_entry(t_data *data, int cmd, int fdin, int fdout)
{
	int	fd;

	if (ft_strncmp(data->token[cmd].tab[0], "./", 2) == 0
		|| ft_strchr(data->token[cmd].tab[0], '/') != NULL)
	{
		fd = open(data->token[cmd].tab[0], O_WRONLY);
		if (errno == EISDIR)
			return (ft_close(data, fdin, fdout, cmd),
				perror(data->token[cmd].tab[0]), 126);
		else if (errno == ENOENT)
			return (ft_close(data, fdin, fdout, cmd),
				perror(data->token[cmd].tab[0]), 127);
		if (fd >= 0)
			close(fd);
		fd = access(data->token[cmd].tab[0], X_OK);
		if (fd != 0 && errno == EACCES)
			return (ft_close(data, fdin, fdout, cmd),
				perror(data->token[cmd].tab[0]), 126);
	}
	return (0);
}
