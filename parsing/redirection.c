/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:48:22 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/02 13:27:29 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
}

int	ft_execute(char *full_path, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;

	printf("full path = %s, cmd = %s\n", full_path, cmd_tab[0]);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1
			|| dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		execve(full_path, cmd_tab, NULL);
		return (1);
	}
	ft_close(fdin, fdout);
	return (0);
}

int   open_file(t_token token, int i)
{
	int fd;

	fd = 0;
	if(i == 0)
		fd = open(token.litteral[0], O_RDONLY);
	else if (i == 1)
		fd = open(token.litteral[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return(perror(token.litteral[0]), -1);
	return(fd);
}

int    execution(t_data *data)
{
	int i;
	int fdin;
	int fdout;
	int cmd;
	int n_pipe[2];
	pid_t	pid;
	int *status;

	pid = 0;
	status = 0;
	i = 0;
	if (pipe(n_pipe) == -1)
		return (perror("pipe"), 1);
	while(i <= data->lenght_token)
	{
		fdin = n_pipe[0];
		fdout = n_pipe[1];
		cmd = -1;
		while(i < data->lenght_token && data->token[i].type != pipes)
		{
			if(data->token[i].type == command || data->token[i].type == built_in)
				cmd = i;
			else if(data->token[i].type == infile)
				fdin = open_file(data->token[i], 0);
			else if(data->token[i].type == outfile)
				fdout = open_file(data->token[i], 1);
			if(fdin == -1 || fdout == -1)
			{
				while(i < data->lenght_token && data->token[i].type != pipes)
					i++;
				cmd = -1;
				break;
			}   
			i++;
		}
		if(cmd != -1)
			ft_execute(data->token[cmd].full_path, data->token[cmd].litteral, fdin, fdout);
		i++;
	}
	while (pid != -1)
	{
		pid = waitpid(-1, status, 0);
		if (!WIFEXITED(*status) || WEXITSTATUS(*status) != 0)
			return (ft_close(n_pipe[0], n_pipe[1]), 1);
	}
	return(0);
}
