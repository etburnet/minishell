/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/24 12:56:30 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	t_pipe_cmd	*pipe_cmd;
	int			ret;

	if (argc >= 5)
	{
		pipe_cmd = malloc(sizeof(t_pipe_cmd));
		if (!pipe_cmd)
			return (1);
		pipe_cmd->fd1 = -1;
		pipe_cmd->fd2 = -1;
		ret = ft_execute(argv, argc, *pipe_cmd);
		ft_close(pipe_cmd->fd1, pipe_cmd->fd2);
		free(pipe_cmd);
		return (ret);
	}
	else
		return (ft_putstr_fd("4 args Minimum", 2), 1);
=======
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/23 17:31:42 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct sigaction	action;
	char				*arg;

	action.sa_handler = &handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &action, NULL);
	while (1)
	{
		arg = readline("minishell$ ");
		if (arg == NULL || ft_strncmp(arg, "exit", 5) == 0)// faire split pour "exit      "
			ft_exit(arg);
		if (*arg)
		{
			add_history(arg);
			check_arg(arg);
			free(arg);
		}
	}
	return (0);
>>>>>>> pipex
}
