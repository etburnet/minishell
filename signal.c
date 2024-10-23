/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/23 23:50:36 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_recieved = 0;

void	ft_child_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
		g_sig_recieved = 1;
		exit(g_sig_recieved);
	}
}

void	ft_here_doc_signal(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		g_sig_recieved = -1;
	}
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_sig_recieved = 1;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
