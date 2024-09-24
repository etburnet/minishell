/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:37:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/24 12:31:36 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_forking(t_pipe_cmd pipe_cmd, int fdin, int fdout)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1
			|| dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		if (pipe_cmd.fd2 > 0)
			ft_close(pipe_cmd.fd_pipe[0], pipe_cmd.fd2);
		ft_close(pipe_cmd.fd_pipe[0], pipe_cmd.fd_pipe[1]);
		execve(pipe_cmd.cmd_path, pipe_cmd.cmd_tab, NULL);
		free(pipe_cmd.cmd_path);
		return (ft_free_all(&pipe_cmd.cmd_tab, "execve"));
	}
	ft_close(fdin, fdout);
	return (0);
}

int	ft_prepare_fds(t_pipe_cmd pipe_cmd, int *fdin, int *fdout, int i)
{
	if (i == 1)
	{
		*fdin = pipe_cmd.fd1;
		*fdout = pipe_cmd.fd_pipe[1];
	}	
	else if (i == 2)
	{
		*fdin = pipe_cmd.fd_pipe[0];
		*fdout = pipe_cmd.fd2;
	}
	else
	{
		*fdin = pipe_cmd.fd_pipe[0];
		*fdout = pipe_cmd.fd_pipe[1];
	}
	return (0);
}

int	ft_path(char *cmd, t_pipe_cmd pipe_cmd, int i)
{
	int	ret;
	int	fdout;
	int	fdin;

	ft_prepare_fds(pipe_cmd, &fdin, &fdout, i);
	pipe_cmd.cmd_tab = ft_split(cmd, ' ');
	if (pipe_cmd.cmd_tab == NULL)
		return (perror("ft_split"), 1);
	pipe_cmd.cmd_path = ft_find_cmd(pipe_cmd.cmd_tab);
	if (pipe_cmd.cmd_path == NULL)
		return (ft_free_split(pipe_cmd.cmd_tab), 1);
	ret = ft_forking(pipe_cmd, fdin, fdout);
	close(pipe_cmd.fd_pipe[1]);
	ft_free_split(pipe_cmd.cmd_tab);
	free(pipe_cmd.cmd_path);
	return (ret);
}

void	ft_is_file_ok(char **argv, int argc, t_pipe_cmd pipe_cmd, int i)
{
	if (i == 1)
	{
		pipe_cmd.fd1 = open(argv[1], O_RDONLY);
		if (pipe_cmd.fd1 < 0)
			return (perror(argv[1]));
		if (ft_path(argv[2], pipe_cmd, i) == 1)
		{
			ft_putstr_fd("Command not found\n", 2);
			close(pipe_cmd.fd1);
		}
	}
	else if (i == 2)
	{
		pipe_cmd.fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipe_cmd.fd2 < 0)
			return (perror(argv[argc - 1]));
		if (ft_path(argv[argc - 2], pipe_cmd, i) == 1)
			ft_putstr_fd("Last command not found\n", 2);
	}
}

int	ft_execute(char **argv, int argc, t_pipe_cmd p)
{
	int		i;
	int		status;
	int		next_pipe[2];
	pid_t	pid;

	i = 2;
	status = 0;
	pid = 0;
	if (ft_create_pipe(p.fd_pipe))
		return (1);
	ft_is_file_ok(argv, argc, p, 1);
	while (argv[i++] != NULL && i < argc - 2)
	{
		if (ft_create_pipe(next_pipe))
			return (1);
		p.fd_pipe[1] = next_pipe[1];
		if (ft_path(argv[i], p, 3) == 1)
			ft_putstr_fd("Command not found\n", 2);
		close(p.fd_pipe[0]);
		p.fd_pipe[0] = next_pipe[0];
	}
	ft_is_file_ok(argv, argc, p, 2);
	ft_close(p.fd2, p.fd1);
	return (ft_wait_all(&status, p));
}
