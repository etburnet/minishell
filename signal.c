/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/18 19:23:32 by eburnet          ###   ########.fr       */
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
	if(signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_sig_recieved = 2;
	}
}


void	init_signal_handler(t_data *data, int i)
{
	struct sigaction	sa;
	struct sigaction	action;
	(void)data;
	
	if (i == 1 || i == 3)
	{
		ft_memset(&action, 0, sizeof(action));
		action.sa_handler = &handle_signal;
		sigaction(SIGINT, &action, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 2)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &handle_sig_heredoc;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 4)
	{
		ft_memset(&action, 0, sizeof(action));
		action.sa_handler = &handle_signal_fork;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else if (i == 5)
	{
		signal(SIGQUIT, SIG_DFL);
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