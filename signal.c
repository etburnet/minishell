/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/11/05 16:39:28 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_recieved = 0;

void	ft_child_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
		g_sig_recieved = 130;
		exit(g_sig_recieved);
	}
}

void	ft_here_doc_signal(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		ft_putstr_fd("\n", 2);
		g_sig_recieved = 1;
	}
}

void	ft_signal(int signum)
{
	if (signum == SIGINT && g_sig_recieved == 13)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGINT)
	{
		g_sig_recieved = 130;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_check_signal(int status)
{
	if (status == 2)
	{
		ft_putstr_fd("\n", 2);
		g_sig_recieved = 130;
	}
	if (status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}
