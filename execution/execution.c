/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:54:09 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/22 11:36:58 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute(t_data *data, t_token tok, int fdin, int fdout)
{
	pid_t	pid;
	int		fd;

	fd = open(tok.tab[0], O_WRONLY);
	if (errno == EISDIR)
		return (ft_close(data, fdin, fdout),
			put_error("is a directory: ", tok.tab[0]), 126);
	// close(fd);
	if (!tok.full_path)
		return (put_error(ERR_CMD, tok.tab[0]), ft_close(data, fdin, fdout),
			127);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid > 0)
		init_signal_handler(data, 4);
	else if (pid == 0)
	{
		if (ft_child(data, tok, fdin, fdout) == 1)
			return (1);
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
		ret = ft_execute(data, data->token[cmd], token.fdin, token.fdout);
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
		if(*i < data->lenght_token)
			manage_files(data, data->token[*i], &data->token[cmd]);
		if (*i < data->lenght_token && (data->token[cmd].fdin == -1 || data->token[cmd].fdout == -1))
		{
			while (*i < data->lenght_token && data->token[*i].type != pipes)
				(*i)++;
			if (*i == data->lenght_token)
				return (-1);
		}
		(*i)++;
	}
	return (cmd);
}

int    prepare_fd(t_data *data)
{
    t_token    tok;
    int        i;
    int        cmd;
    int        ret;

    i = 0;
    while (i < data->lenght_token)
    {
        cmd = bring_command(data, &i);
        if (cmd == -1)
            return (-1);
        tok = data->token[cmd];
        if (manage_pipe(data, &tok))
            return (1);
        ret = dispatch_cmd(data, tok, cmd);
        if (command_return(data, tok, ret))
            return (command_return(data, tok, ret));
        i++;
    }
    return (ret);
}

int    execution(t_data *data)
{
    pid_t    pid;
    int        status;
    int        ret;

    status = 0;
    pid = 0;
    check_first_last(data);
    ret = prepare_fd(data);
    if (ret == -1)
        return (1);
    if (ret != 0)
        return (data->status = ret % 255, ret);
    while (pid != -1)
    {
        pid = waitpid(-1, &status, 0);
        data->status = status % 255;
        if (WEXITSTATUS(status) != 0)
            return (1);
    }
    return (0);
}
