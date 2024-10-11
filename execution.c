/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/11 17:39:20 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_built_in(t_data *data, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		ret = which_builtin(data, cmd_tab);
		ft_close(data->pipe_fd[0], data->pipe_fd[1]);
		ft_close(data->old_pipe[0], data->old_pipe[1]);
		exit(0);
	}
	ft_close(fdin, fdout);
	return (ret);
}

int	ft_execute(t_data *data, int cmd, int fdin, int fdout)
{
	pid_t	pid;

	printf("fdin %d, fdout %d\n", fdin, fdout);
	if (data->token[cmd].full_path == NULL)
		return (put_error(ERR_CMD, data->token[cmd].litteral[0]), ft_close(fdin, fdout), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		ft_close(data->pipe_fd[0], data->pipe_fd[1]);
		ft_close(data->old_pipe[0], data->old_pipe[1]);
		if (execve(data->token[cmd].full_path, data->token[cmd].litteral, NULL) == -1)
			put_error(ERR_CMD, data->token[cmd].litteral[0]);
		return (1);
	}
	ft_close(fdin, fdout);
	return (0);
}

int	dispatch_cmd(t_data *data, int cmd)
{
	int	ret;

	ret = 0;
	if (data->token[cmd].type == command)
		ret = ft_execute(data, cmd, data->token[cmd].fdin,
				data->token[cmd].fdout);
	else if (data->token[cmd].type == built_in)
	{
		if (strncmp(data->token[cmd].litteral[0], "exit", 5) == 0 && data->token[cmd].last == 1
			&& data->token[cmd].first == 1)
			ret = ft_exit(data, data->token[cmd].litteral, 0);
		else if (strncmp(data->token[cmd].litteral[0], "cd", 5) == 0 && data->token[cmd].last == 1
			&& data->token[cmd].first == 1)
			ret = cd(data, data->token[cmd].litteral);
		else if (strncmp(data->token[cmd].litteral[0], "unset", 5) == 0 && data->token[cmd].last == 1
			&& data->token[cmd].first == 1)
			ret = unset(data, data->token[cmd].litteral);
		else if (strncmp(data->token[cmd].litteral[0], "export", 5) == 0 && data->token[cmd].last == 1
			&& data->token[cmd].first == 1)
			ret = export(data, data->token[cmd].litteral);
		else
			ret = exec_built_in(data, data->token[cmd].litteral, data->token[cmd].fdin, data->token[cmd].fdout);
	}
	if (ret != 0)
		ft_close(data->token[cmd].fdin, data->token[cmd].fdout);
	return (ret);
}

int	bring_command(t_data *data, int *i)
{
	int	cmd;
	int	tmp;

	tmp = -1;
	cmd = -1;
	while (*i < data->lenght_token && data->token[*i].type != pipes)
	{
		if (data->token[*i].type == command || data->token[*i].type == built_in)
			cmd = *i;
		else if (cmd == -1 && data->token[*i].type == infile)
			tmp = open_file(data->token[*i], 0);
		else if (data->token[*i].type == infile)
			data->token[cmd].fdin = open_file(data->token[*i], 0);
		else if (data->token[*i].type == outfile)
			data->token[cmd].fdout = open_file(data->token[*i], 1);
		if (data->token[cmd].fdin == -1 || data->token[cmd].fdout == -1)
		{
			while (*i < data->lenght_token && data->token[*i].type != pipes)
				(*i)++;
			cmd = -1;
			break ;
		}
		(*i)++;
	}
	if (data->token[cmd].fdin == 0 && tmp > 0)
	{
		data->token[cmd].fdin = tmp;
		tmp = -1;
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
	check_first_last(data);
	while (i < data->lenght_token)
	{
		cmd = bring_command(data, &i);
		if (pipe(data->pipe_fd) == -1)
			return (perror("pipe"), 1);
		if (data->token[cmd].first != 1
			&& data->token[cmd].fdin == STDIN_FILENO)
			data->token[cmd].fdin = data->old_pipe[0];
		data->old_pipe[0] = data->pipe_fd[0];
		if (data->token[cmd].last != 1
			&& data->token[cmd].fdout == STDOUT_FILENO)
			data->token[cmd].fdout = data->pipe_fd[1];
		data->old_pipe[1] = data->pipe_fd[1];
		ret = dispatch_cmd(data, cmd);
		if (ret != 0)
			return (ret);
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
	ret = prepare_fd(data);
	if (ret != 0)
		return (ret);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		data->status = status;
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}
