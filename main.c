/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/30 16:51:04 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct sigaction	action;
	t_data				*data;
	t_data				tok;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	action.sa_handler = &handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &action, NULL);
	if (copy_env(data) == 3)
		return (ERR_MALLOC, ft_exit(data), 1);
	if (update_shlvl(data) == 3)
		return (ERR_MALLOC, ft_exit(data), 1);
	data->input = malloc(sizeof(char *) * 3);
	data->input[0] = "export";
	data->input[1] = "varest=545";
	data->input[2] = NULL;
	if (export(data) == 3)
		return (ERR_MALLOC, ft_exit(data), 1);
	// cd(data);
	//print_env(data);
	while (1)
	{
		data->arg = readline("minishell$ ");
		if (data->arg == NULL)
			ft_exit(data);
		if (*data->arg)
		{
			add_history(data->arg);
			init_data(&tok, data->arg);
			search_token(tok.source, &tok);
			free(data->arg);
		}
	}
	return (0);
}
