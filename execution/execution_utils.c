/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:19:29 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/23 14:04:06 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	there_is_pipe(t_data *data, int cmd)
{
	int i;

	i = cmd;
	while(i < data->lenght_token)
	{
		if(data->token[i].type == pipes)
			data->token[cmd].last = 0;
		i++;
	}
	data->token[i].last = 1;
}

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
	there_is_pipe(data, cmd);
}

void	ft_close(t_data *data, int fd1, int fd2, int cmd)
{
	if (fd1 > 0 && fd1 != STDIN_FILENO)
		close(fd1);
	if (fd2 > 0 && fd2 != STDOUT_FILENO)
		close(fd2);
	if (cmd > -1 && data->token[cmd].here_doc != NULL)
	{
		if(data->token[cmd].fdin)
			close(data->token[cmd].fdin);
		unlink(data->token[cmd].here_doc);
		// ft_free(data->token[cmd].here_doc);
	}
}
int		create_hd_file(t_data *data, int cmd)
{
	char *itoa;
	
	itoa = ft_itoa(cmd);
	if(itoa == NULL)
		return(put_error(ERR_MALLOC, NULL), 3);
	if(data->token[cmd].here_doc != NULL)
		ft_free(data->token[cmd].here_doc);
	data->token[cmd].here_doc = ft_strjoin("temp_file_here_doc", itoa);
	ft_free(itoa);
	return(0);
}
int	open_file(t_data *data, t_token token, int i, int cmd)
{
	int	fd;
	
	
	fd = 0;
	if (i == 0)
		fd = open(token.tab[0], O_RDONLY);
	else if (i == 1)
		fd = open(token.tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 3)
	{
		if(create_hd_file(data, cmd) == 3)
			return(-1);
		fd = open(data->token[cmd].here_doc , O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("temp_file_here_doc"), -1);
	}
	else if (i == 4)
		fd = open(data->token[cmd].here_doc, O_RDONLY);
	else if (i == 5)
		fd = open(token.tab[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(token.tab[0]), data->status = 1, -1);
	return (fd);
}

int	catch_cmd(t_data *data, int i)
{
	while (i < data->lenght_token && data->token[i].type != pipes)
	{
		if (data->token[i].type == command || data->token[i].type == built_in || data->token[i].type == variable)
			return (i);
		i++;
	}
	return (-1);
}

void	close_all(t_data *data, int fdin, int fdout, int cmd)
{
	ft_close(data, fdin, fdout, cmd);
	ft_close(data, data->pipe_fd[0], data->pipe_fd[1], -1);
	ft_close(data, data->old_pipe[0], data->old_pipe[1], -1);
}
