/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/24 17:31:14 by eburnet          ###   ########.fr       */
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
}
