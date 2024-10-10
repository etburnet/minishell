/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/10 15:38:18 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		ft_minishell(char *s, t_data *data)
{
	int	ret;

	ret = search_token(s, data);
	if(ret != 0)
		return(ret);
	ret = identify_token(data);
	if(ret != 0)
		return(ret);
	ret = identify_command(data);
	if(ret != 0)
		return(ret);
	execution(data);
	free_data_token(data);
	return(0);
}

int	main(void)
{
	t_data				*data;
	int ret;

	ret = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_signal_handler(1);
	if (copy_env(data) == 3)
		ft_exit(data, NULL, 3);
	if (update_shlvl(data) == 3)
		ft_exit(data, NULL, 3);
	while (1)
	{
		data->arg = readline("minishell$ ");
		if (data->arg == NULL)
			ft_exit(data, NULL, 1);
		if (*data->arg)
		{
			add_history(data->arg);
			ret = init_data(data, data->arg);
			if(ret != 0)
				return(ret);
			ret = ft_minishell(data->source, data);
			if(ret != 0)
				return(ft_clean(data), ret);
		}
	}
	return (0);
}
