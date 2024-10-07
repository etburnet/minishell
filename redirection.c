/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:48:22 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/07 17:14:06 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 0 && fd1 != STDIN_FILENO)
		close(fd1);
	if (fd2 > 0 && fd2 != STDOUT_FILENO)
		close(fd2);
}

int	open_file(t_token token, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(token.litteral[0], O_RDONLY);
	else if (i == 1)
		fd = open(token.litteral[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(token.litteral[0]), -1);
	return (fd);
}

int which_builtin(t_data *data, char **cmd_tab)
{
	int ret;
	
	ret = 0;
	if (strncmp(cmd_tab[0], "echo", 5) == 0)
		ret = echo(cmd_tab);
	else if(strncmp(cmd_tab[0], "cd", 3) == 0)
		ret = cd(data, cmd_tab);
	else if(strncmp(cmd_tab[0], "pwd", 4) == 0)
		ret = pwd();
	else if(strncmp(cmd_tab[0], "export", 7) == 0)
		ret = export(data, cmd_tab);
	else if(strncmp(cmd_tab[0], "unset", 6) == 0)
		ret = unset(data, cmd_tab);
	else if(strncmp(cmd_tab[0], "env", 4) == 0)
		ret = print_env(data);
	else if(strncmp(cmd_tab[0], "exit", 5) == 0)
		ret = ft_exit(data, cmd_tab, 0);
	else
		return (put_error("This is not a builtin:", cmd_tab[0]), 1);	
	return (ret);
}

int	exec_built_in(t_data *data, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

	//printf("built Fork fdin %d, fdout %d\n", fdin, fdout);
	ret = -1;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		ret = which_builtin(data, cmd_tab);
		// printf("ret = %d\n", ret);
		exit(0);
	}
	ft_close(fdin, fdout);
	return (ret);
}

int	ft_execute(char *full_path, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;

	// printf("ex: %s Fork fdin %d, fdout %d\n",cmd_tab[0], fdin, fdout);
	if (full_path == NULL)
	{
		put_error("Command not found: ", cmd_tab[0]);
		ft_close(fdin, fdout);
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("OUT dup2"), 1);
		ft_close(fdin, fdout);
		if (execve(full_path, cmd_tab, NULL) == -1)
			put_error("Command not found: ", cmd_tab[0]);
		return (1);
	}
	ft_close(fdin, fdout);
	return (0);
}

void	check_first_last(t_data *data)
{
	int i;
	int cmd;
	int first;
	
	first = 0;
	i = 0;
	cmd = 0;
	if (i == 0)
		data->token[i].first = 1;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == command || data->token[i].type == built_in)
		{	
			cmd = i;
			if(first == 0)
			{
				first = 1;
				data->token[i].first = 1;
			}
		}
		i++;
	}
	// if (i == data->lenght_token)
	data->token[cmd].last = 1;
}

int		bring_command(t_data *data, int *i)
{
	int cmd;

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
	return(cmd);
}

int		prepare_fd(t_data *data, t_token token, int *pipe_fd)
{
	if(token.first != 1 && token.fdin == STDIN_FILENO)
		token.fdin = pipe_fd[0];
	if(token.last != 1 && token.fdout == STDOUT_FILENO)
		token.fdout = pipe_fd[1];
	if (token.type == command)
		ft_execute(token.full_path, token.litteral, token.fdin, token.fdout);
	if (token.type == built_in)
	{
		if(strncmp(token.litteral[0], "exit", 5) == 0 && token.last == 1 && token.first == 1)
			ft_exit(data, token.litteral, 0);
		exec_built_in(data, token.litteral, token.fdin, token.fdout);
	}
	return(0);
}

int		prepare_exec(t_data *data, int *pipe_fd)
{
	int i;
	int		next_pipe[2];
	int cmd;
	
	
	i = 0;
	cmd = -1;
	check_first_last(data);
	while(i < data->lenght_token)
	{
		if (pipe(next_pipe) == -1)
			return (perror("pipe"), 1);
		cmd = bring_command(data, &i);
		pipe_fd[1] = next_pipe[1];
		prepare_fd(data, data->token[cmd], pipe_fd);
		close (pipe_fd[0]);
		pipe_fd[0] = next_pipe[0];
		i++;
	}
	ft_close(next_pipe[0], next_pipe[1]);
	return(0);
}

int		execution(t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	
	status = 0;
	pid = 0;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	prepare_exec(data, pipe_fd);
	ft_close(pipe_fd[0], pipe_fd[1]);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			return (ft_close(pipe_fd[0], pipe_fd[1]), 1);
	}
	return (ft_close(pipe_fd[0], pipe_fd[1]), 0);
}
