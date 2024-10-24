/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:54:09 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/24 18:31:56 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute(t_data *data, int cmd, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

//	printf("fdin %d, fdout %d\n", fdin, fdout);
	ret = ft_check_entry(data, cmd, fdin, fdout);
	if (ret != 0)
		return (ret);
	pid = fork();
	data->last_pid = pid;
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid > 0)
		init_signal_handler(data, 4);
	else if (pid == 0)
	{
		if(fdin < 0 || fdout < 0)
			return(1);
		ret = ft_child(data, cmd, fdin, fdout);
		return (ret);
	}
	//printf("ici\n");
	ft_close(data, fdin, fdout, cmd);
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
	if (token.type == command || token.type == variable)
		ret = ft_execute(data, cmd, token.fdin, token.fdout);
	else if (token.type == built_in)
	{
		if (ft_strncmp(token.tab[0], "exit", 5) == 0 && alone == 1)
			ret = ft_exit(data, token.tab, 0, 0);
		else if (ft_strncmp(token.tab[0], "cd", 5) == 0 && alone == 1)
			ret = cd(data, token.tab);
		else if (ft_strncmp(token.tab[0], "unset", 5) == 0 && alone == 1)
			ret = unset(data, token.tab);
		else if (ft_strncmp(token.tab[0], "export", 5) == 0 && alone == 1)
			ret = export(data, token.tab);
		else
			ret = exec_built_in(data, cmd, token.fdin, token.fdout);
	}
	return (ret);
}

int	bring_command(t_data *data, int *i)
{
	int	cmd;

	cmd = -1;
	while (*i < data->lenght_token && data->token[*i].type != pipes)
	{
		//printf("1 %s\n", data->token[*i].tab[0]);
		if (cmd < 0)
			cmd = catch_cmd(data, *i);
		if (cmd >= 0 && data->token[cmd].tab[0][0] == '\0')
			cmd = catch_cmd(data, ++(*i));
		if (cmd == -1)
			while (*i < data->lenght_token - 1 && data->token[*i].type != pipes && data->token[*i].type != infile && data->token[*i].type != outfile && data->token[*i].type != append)
				(*i)++;
		if (*i < data->lenght_token)
			manage_files(data, data->token[*i], &data->token[cmd], &cmd);
		if (cmd == -2)
			while (*i < data->lenght_token && data->token[*i].type != pipes)
				(*i)++;
		if (cmd >= 0 && *i < data->lenght_token && (data->token[cmd].fdin == -1
				|| data->token[cmd].fdout == -1))
		{
			while (*i < data->lenght_token && data->token[*i].type != pipes)
				(*i)++;
			if (*i == data->lenght_token)
				return (-1);
			if(data->token[*i].type == pipes)
				return(cmd);
			if(data->token[*i].last == 1)
				close_all(data, -1, -1, cmd);
		}
		(*i)++;
	}	
	return (cmd);
}

int	prepare_fd(t_data *data)
{
	t_token	tok;
	int		i;
	int		cmd;
	int		ret;

	i = 0;
	ret = 0;
	while (i < data->lenght_token)
	{
		cmd = bring_command(data, &i);
		if (cmd == -1)
			return (-1);
		tok = data->token[cmd];
		if (manage_pipe(data, &tok))
			return (1);
		if (tok.fdin >= 0 && tok.fdout >= 1)
			ret = dispatch_cmd(data, tok, cmd);
		if (command_return(data, tok, ret))
			return (command_return(data, tok, ret));
		i++;
	}
	return (ret);
}

int	execution(t_data *data)
{
	pid_t	pid;
	int		status;
	int		ret;

	status = 0;
	pid = 0;
	data->last_pid = 0;
	check_first_last(data);
	ret = prepare_fd(data);
	if (ret == -1)
		return (1);
	if (ret != 0)
		return (data->status = ret % 255, ret);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		//printf("%d\n", status);
		if (pid == data->last_pid)
			data->status = status % 255;
		if (WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}
