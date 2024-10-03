/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/03 11:49:36 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct sigaction	action;
	t_data				*data;
	// t_data				tok;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	action.sa_handler = &handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &action, NULL);
	if (copy_env(data) == 3)
		ft_exit(data, NULL, 3);
	if (update_shlvl(data) == 3)
		ft_exit(data, NULL, 3);
	char *tab[2];
	tab[0] = "export";
	tab[1] = "894894";
	//ft_exit(data, tab, 0);
	while (1)
	{
		data->arg = readline("minishell$ ");
		if (data->arg == NULL)
			ft_exit(data, NULL, 1);
		if (*data->arg)
		{
			add_history(data->arg);
			init_data(data, data->arg);
			search_token(data->source, data);
			// execution(&data);
			free(data->arg);
		}
	}
	return (0);
}
