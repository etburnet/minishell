/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:54:09 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/21 16:41:26 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute(t_data *data, t_token tok, int fdin, int fdout)
{
	pid_t	pid;
	DIR		*stream_dir;

	stream_dir = opendir(tok.tab[0]);
	if (stream_dir != NULL)
	{
		put_error("is a directory: ", tok.tab[0]);
		return (closedir(stream_dir), ft_close(data, fdin, fdout), 126);
	}
	if (!tok.full_path || tok.tab[0][0] == '\0')
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
		manage_files(data, data->token[*i], &data->token[cmd]);
		if (data->token[cmd].fdin == -1 || data->token[cmd].fdout == -1)
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

int	prepare_fd(t_data *data)
{
	t_token	tok;
	int		i;
	int		cmd;
	int		ret;

	i = 0;
	while (i < data->lenght_token)
	{
		cmd = bring_command(data, &i);
		if (cmd == -1)
			return (1);
		tok = data->token[cmd];
		if (handle_pipe_and_fd(data, &tok))
			return (1);
		ret = dispatch_cmd(data, tok, cmd);
		if (handle_command_return(data, tok, ret))
			return (handle_command_return(data, tok, ret));
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
	check_first_last(data);
	ret = prepare_fd(data);
	if (ret != 0)
		return (data->status = ret % 255, ret);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		data->status = status % 255;
		if (WEXITSTATUS(status) != 0)
			return (1);
		// else if (WIFSIGNALED(status))
        // {
		// 	if(atoi(&data->cp_env[get_this_env("SHLVL", data->cp_env)][6]) <= 2)
        //     {
		// 		if (WTERMSIG(status) == SIGINT)
        //        		printf("sigint recu\n", WTERMSIG(status));
        //     	if (WTERMSIG(status) == SIGQUIT)
        //         	printf("Quit (core dumped)\n", WTERMSIG(status));}
        // }
	}
	// init_signal_handler(data, 1);
	return (0);
}
