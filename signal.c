/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/09 15:45:01 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig_recieved = 0;

void    init_signal_handler(int i)
{
    struct sigaction	sa;
    struct sigaction	action;
    
    if(i == 1)
    {    
        ft_memset(&action, 0, sizeof(action));
        action.sa_handler = &handle_signal;
        sigaction(SIGINT, &action, NULL);
        signal(SIGQUIT, SIG_IGN);
    }
    else if(i == 2)
    {    
        ft_memset(&sa, 0, sizeof(sa));
        sa.sa_handler = &handle_sig_heredoc;
        sigaction(SIGINT, &sa, NULL);
    }
	else if(i == 3)
	{
        ft_memset(&action, 0, sizeof(action));
		action.sa_handler = &handle_signal;
        sigaction(SIGINT, &action, NULL);
	}
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}