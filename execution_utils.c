/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:19:29 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/18 19:01:02 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_first_last(t_data *data)
{
	int	i;
	int	cmd;
	int	first;

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
			if (first == 0)
			{
				first = 1;
				data->token[i].first = 1;
			}
		}
		i++;
	}
	data->token[cmd].last = 1;
}

void	ft_close(t_data *data, int fd1, int fd2)
{
	if (fd1 > 0 && fd1 != STDIN_FILENO)
		close(fd1);
	if (fd2 > 0 && fd2 != STDOUT_FILENO)
		close(fd2);
	if (data->here == 1)
		unlink("temp_file_here_doc.txt");
}

int	open_file(t_data *data, t_token token, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(token.tab[0], O_RDONLY);
	else if (i == 1)
		fd = open(token.tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 3)
	{
		fd = open("temp_file_here_doc.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("temp_file_here_doc.txt"), -1);
		data->here = 1;
	}
	else if (i == 4)
		fd = open("temp_file_here_doc.txt", O_RDONLY);
	else if (i == 5)
		fd = open(token.tab[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(token.tab[0]), data->status = 1, -1);
	return (fd);
}

int	which_builtin(t_data *data, char **cmd_tab)
{
	int	ret;

	ret = 0;
	if (strncmp(cmd_tab[0], "echo", 5) == 0)
		ret = echo(cmd_tab);
	else if (strncmp(cmd_tab[0], "cd", 3) == 0)
		ret = cd(data, cmd_tab);
	else if (strncmp(cmd_tab[0], "pwd", 4) == 0)
		ret = pwd(data);
	else if (strncmp(cmd_tab[0], "export", 7) == 0)
		ret = export(data, cmd_tab);
	else if (strncmp(cmd_tab[0], "unset", 6) == 0)
		ret = unset(data, cmd_tab);
	else if (strncmp(cmd_tab[0], "cp_env", 4) == 0)
		ret = print_env(data);
	else if (strncmp(cmd_tab[0], "exit", 5) == 0)
		ret = ft_exit(data, cmd_tab, 0);
	else
		return (put_error(ERR_CMD, cmd_tab[0]), 2);
	return (ret);
}

int	catch_cmd(t_data *data, int i)
{
	while (i < data->lenght_token && data->token[i].type != pipes)
	{
		if (data->token[i].type == command || data->token[i].type == built_in)
			return (i);
		i++;
	}
	return (-1);
}

void	close_all(t_data *data, int fdin, int fdout)
{
	ft_close(data, fdin, fdout);
	ft_close(data, data->pipe_fd[0], data->pipe_fd[1]);
	ft_close(data, data->old_pipe[0], data->old_pipe[1]);
}
