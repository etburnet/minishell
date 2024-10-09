/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/09 17:17:39 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		ft_minishell(char *s, t_data *data)
{
	if(search_token(s, data) == -1)
		return(-1);
	if(identify_token(data) == -1)
		return(-1);
	identify_command(data);
	execution(data);
	free_data_token(data);
	return(0);
}

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
			if(init_data(data, data->arg) == -1)
				return(-1);
			if(ft_minishell(data->source, data) == -1)
				return(ft_clean(data), -1);
			// free(data->arg);
		}
	}
	return (0);
}
