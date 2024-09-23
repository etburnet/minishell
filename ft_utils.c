/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:42:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/23 16:46:43 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free (tab[i++]);
	free (tab);
}

int	ft_free_all(char ***cmd_tab, char *error)
{
	ft_free_split(*cmd_tab);
	ft_putstr_fd(error, 2);
	return (1);
}

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
}

int	ft_create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	return (0);
}

int	ft_wait_all(int *status, t_pipe_cmd p)
{
	pid_t	pid;

	pid = 0;
	ft_close(p.fd_pipe[0], p.fd_pipe[1]);
	while (pid != -1)
	{
		pid = waitpid(-1, status, 0);
		if (!WIFEXITED(*status) || WEXITSTATUS(*status) != 0)
			return (ft_close(p.fd_pipe[0], p.fd_pipe[1]), 1);
	}
	return (ft_close(p.fd_pipe[0], p.fd_pipe[1]), 0);
}
