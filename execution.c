/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/16 16:27:37 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_built_in(t_data *data, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	// printf("fdin %d, fdout %d, append %d\n", fdin, fdout, data->append_id);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (dup2(fdin, 0) == -1 || dup2(fdout, data->append_id) == -1)
			return (perror("dup2"), 1);
		close_all(data, fdin, fdout);
		ret = which_builtin(data, cmd_tab);
		exit(0);
	}
	ft_close(data, fdin, fdout);
	return (ret);
}

int	ft_execute(t_data *data, int cmd, int fdin, int fdout)
{
	pid_t	pid;

	// printf("fdin %d, fdout %d, append %d\n", fdin, fdout, data->append_id);
	if (data->token[cmd].full_path == NULL)
		return (put_error(ERR_CMD, data->token[cmd].tab[0]), ft_close(data, 
				fdin, fdout), 127);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid > 0)
		init_signal_handler(4);
	else if (pid == 0)
	{
		if (dup2(fdin, 0) == -1 || dup2(fdout, data->append_id) == -1)
			return (perror("dup2"), 1);
		close_all(data, fdin, fdout);
		if (execve(data->token[cmd].full_path, data->token[cmd].tab, NULL) ==
			-1)
			put_error(ERR_CMD, data->token[cmd].tab[0]);
		return (2);
	}
	ft_close(data, fdin, fdout);
	return (0);
}

int	dispatch_cmd(t_data *data, t_token token, int cmd)
{
	int	ret;
	int	alone;

	ret = 0;
	alone = 0;
	if (token.last == 1 && token.first == 1)
		alone = 1;
	if (token.type == command)
		ret = ft_execute(data, cmd, token.fdin, token.fdout);
	else if (token.type == built_in)
	{
		if (strncmp(token.tab[0], "exit", 5) == 0 && alone == 1)
			ret = ft_exit(data, token.tab, 0);
		else if (strncmp(token.tab[0], "cd", 5) == 0 && alone == 1)
			ret = cd(data, token.tab);
		else if (strncmp(token.tab[0], "unset", 5) == 0 && alone == 1)
			ret = unset(data, token.tab);
		else if (strncmp(token.tab[0], "export", 5) == 0 && alone == 1)
			ret = export(data, token.tab);
		else
			ret = exec_built_in(data, token.tab, token.fdin, token.fdout);
	}
	return (ret);
}

int	bring_command(t_data *data, int *i)
{
	int	cmd;

	cmd = -1;
	while (*i < data->lenght_token && data->token[*i].type != pipes)
	{
		if (cmd == -1)
			cmd = catch_cmd(data, *i);
		if (cmd == -1)
			while (*i < data->lenght_token && data->token[*i].type != pipes)
				(*i)++;
		else
		{
			if (data->token[*i].type == infile)
				data->token[cmd].fdin = open_file(data, data->token[*i], 0);
			else if (data->token[*i].type == outfile)
				data->token[cmd].fdout = open_file(data, data->token[*i], 1);
			else if (data->token[*i].type == append_out)
				data->token[cmd].fdout = open_file(data, data->token[*i], 5);
			else if (data->token[*i].type == append_id)
				data->append_id = ft_atoi(data->token[*i].tab[0]);
			if (data->token[cmd].fdin == -1 || data->token[cmd].fdout == -1)
			{
				while (*i < data->lenght_token && data->token[*i].type != pipes)
					(*i)++;
				if (*i == data->lenght_token)
					return (-1);
			}
		}
		(*i)++;
	}
	return (cmd);
}

int	prepare_fd(t_data *data)
{
	int	i;
	int	cmd;
	int	ret;

	i = 0;
	cmd = -1;
	while (i < data->lenght_token)
	{
		cmd = bring_command(data, &i);
		if (cmd == -1)
			return (1);
		if (pipe(data->pipe_fd) == -1)
			return (perror("pipe"), 1);
		if (data->token[cmd].first != 1 && data->token[cmd].fdin == 0)
			data->token[cmd].fdin = data->old_pipe[0];
		data->old_pipe[0] = data->pipe_fd[0];
		if (data->token[cmd].last != 1 && data->token[cmd].fdout == 1)
			data->token[cmd].fdout = data->pipe_fd[1];
		data->old_pipe[1] = data->pipe_fd[1];
		ret = dispatch_cmd(data, data->token[cmd], cmd);
		if (ret != 2 && ret != 127 && ret != 0)
			return (ft_close(data, data->token[cmd].fdin, data->token[cmd].fdout),
				data->status = ret % 255, ret);
		i++;
	}
	return (0);
}

int	execution(t_data *data)
{
	pid_t	pid;
	int		status;
	int		ret;

	status = 0;
	pid = 0;
	check_first_last(data);
	ret = prepare_fd(data);
	if (ret != 0)
		return (ret);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		data->status = status % 255;
		if (WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}
