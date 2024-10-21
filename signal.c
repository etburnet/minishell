/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/21 17:10:41 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_recieved = 0;

void	handle_signal_fork(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_sig_recieved = 1;
	}
	if (signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_sig_recieved = 2;
	}
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_sig_recieved = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sig_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_sig_recieved = 1;
		close(0);
		printf("\n");
	}
}

void	ft_signal(void (*handle_function))
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &(*handle_function);
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_handler(t_data *data, int i)
{
	struct sigaction	sa;
	
	(void)data;
	if(atoi(&data->cp_env[get_this_env("SHLVL", data->cp_env)][6]) > 2)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		return;
	}
	if (i == 1 || i == 3)
		ft_signal(handle_signal);
	else if (i == 2)
		ft_signal(handle_sig_heredoc);
	else if (i == 4)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &handle_signal_fork;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (i == 5)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}



