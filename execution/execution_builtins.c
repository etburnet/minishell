/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:55:05 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/23 23:26:48 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_built_in(t_data *data, int cmd, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, ft_child_signal);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(fdin, 0) == -1 || dup2(fdout, data->append_id) == -1)
			return (perror("dup2"), 1);
		close_all(data, fdin, fdout, cmd);
		clear_history();
		ret = which_builtin(data, data->token[cmd].tab);
		ft_clean(data);
		exit(ret);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
