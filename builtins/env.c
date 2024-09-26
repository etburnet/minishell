/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:30:50 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/26 11:02:55 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i])
		printf("%s\n", data->env[i++]);
}


int	ft_copy_env(t_data *data)
{
	int	tab_len;
	int	i;

	i = 0;
	tab_len = 0;
	while (environ[tab_len] != 0)
		tab_len++;
	data->env = malloc(sizeof(char *) * (tab_len + 1));
	if (data->env == NULL)
		return (3);
	data->env[tab_len] = NULL;
	while (i < tab_len)
	{
		data->env[i] = ft_strdup(environ[i]);
		if (data->env[i] == NULL)
			return(free_tab(data->env), 3);
		i++;
	}
	return(0);
}