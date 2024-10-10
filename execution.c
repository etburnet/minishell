/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/10 16:50:23 by eburnet          ###   ########.fr       */
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
		exit(0);
	}
	ft_close(fdin, fdout);
	return (ret);
}


int	ft_execute(char *full_path, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;

	if (full_path == NULL)
		return (put_error(ERR_CMD, cmd_tab[0]), ft_close(fdin, fdout), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		if (execve(full_path, cmd_tab, NULL) == -1)
			put_error(ERR_CMD, cmd_tab[0]);
		return (1);
	}
	ft_close(fdin, fdout);
	return (0);
}


int	bring_command(t_data *data, int *i)
{
	int	cmd;

	cmd = -1;
	while (*i < data->lenght_token && data->token[*i].type != pipes)
	{
		if (data->token[*i].type == command || data->token[*i].type == built_in)
			cmd = *i;
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
	return (cmd);
}

int	prepare_fd(t_data *data, t_token token, int *pipe_fd)
{
	int	ret;

	if (token.first != 1 && token.fdin == STDIN_FILENO)
		token.fdin = pipe_fd[0];
	if (token.last != 1 && token.fdout == STDOUT_FILENO)
		token.fdout = pipe_fd[1];
	if (token.type == command)
		ret = ft_execute(token.full_path, token.litteral, token.fdin,
				token.fdout);
	if (token.type == built_in)
	{
		if (strncmp(token.litteral[0], "exit", 5) == 0 && token.last == 1
			&& token.first == 1)
			ret = ft_exit(data, token.litteral, 0);
		else if (strncmp(token.litteral[0], "cd", 5) == 0 && token.last == 1
			&& token.first == 1)
			ret = cd(data, token.litteral);
		else if (strncmp(token.litteral[0], "unset", 5) == 0 && token.last == 1
			&& token.first == 1)
			ret = unset(data, token.litteral);
		else if (strncmp(token.litteral[0], "export", 5) == 0 && token.last == 1
			&& token.first == 1)
			ret = export(data, token.litteral);
		else
			ret = exec_built_in(data, token.litteral, token.fdin, token.fdout);
	}
	if (ret != 0)
		ft_close(token.fdin, token.fdout);
	return (ret);
}

int	prepare_exec(t_data *data, int *pipe_fd)
{
	int	i;
	int	next_pipe[2];
	int	cmd;
	int	ret;

	i = 0;
	cmd = -1;
	check_first_last(data);
	while (i < data->lenght_token)
	{
		if (pipe(next_pipe) == -1)
			return (perror("pipe"), 1);
		cmd = bring_command(data, &i);
		close(pipe_fd[1]);
		pipe_fd[1] = next_pipe[1];
		ret = prepare_fd(data, data->token[cmd], pipe_fd);
		if (ret != 0)
			return(ft_close(next_pipe[1], next_pipe[0]), ret);
		close(pipe_fd[0]);
		pipe_fd[0] = next_pipe[0];
		close(next_pipe[1]);
		i++;
	}
	ft_close(next_pipe[0], next_pipe[1]);
	return (0);
}

int	execution(t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		ret;

	status = 0;
	pid = 0;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	ret = prepare_exec(data, pipe_fd);
	ft_close(pipe_fd[0], pipe_fd[1]);
	if (ret != 0)
		return(ret);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			return (ft_close(pipe_fd[0], pipe_fd[1]), 1);
	}
	return (ft_close(pipe_fd[0], pipe_fd[1]), 0);
}
