/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:55:05 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/04 16:27:47 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_built_in(t_data *data, int cmd, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	data->last_pid = pid;
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (fdin < 0 || fdout < 0)
		{
			close_all(data, fdin, fdout, cmd);
			exit(0);
		}
		if (dup2(fdin, 0) == -1 || dup2(fdout, data->append_id) == -1)
			return (perror("builtins dup2"), 1);
		clear_history();
		ret = which_builtin(data, data->token[cmd].tab);
		close_all(data, fdin, fdout, cmd);
		ft_clean(data);
		exit(ret);
	}
	ft_close(data, fdin, fdout, cmd);
	return (ret);
}

int	which_builtin(t_data *data, char **cmd_tab)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd_tab[0], "echo", 5) == 0)
		ret = echo(cmd_tab);
	else if (ft_strncmp(cmd_tab[0], "cd", 3) == 0)
		ret = cd(data, cmd_tab);
	else if (ft_strncmp(cmd_tab[0], "pwd", 4) == 0)
		ret = pwd(data);
	else if (ft_strncmp(cmd_tab[0], "export", 7) == 0)
		ret = export(data, cmd_tab);
	else if (ft_strncmp(cmd_tab[0], "unset", 6) == 0)
		ret = unset(data, cmd_tab);
	else if (ft_strncmp(cmd_tab[0], "env", 4) == 0)
		ret = print_env(data);
	else if (ft_strncmp(cmd_tab[0], "exit", 5) == 0)
		ret = ft_exit(data, cmd_tab, 0, 1);
	else
		return (put_error(ERR_CMD, cmd_tab[0]), 2);
	return (ret);
}
