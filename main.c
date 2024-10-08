/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/08 16:27:56 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	main(void)
{
	t_data				*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_signal_handler(1);
	if (copy_env(data) == 3)
		ft_exit(data, NULL, 3);
	if (update_shlvl(data) == 3)
		ft_exit(data, NULL, 3);
	char *tab[2];
	tab[0] = "export";
	tab[1] = "894894";
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
			free(data->arg);
		}
	}
	return (0);
}
