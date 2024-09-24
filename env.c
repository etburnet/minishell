/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:49:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/24 18:10:19 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_copy_env(t_data *data)
{
	int	len;
	int	max_len;
	int	tab_len;

	max_len = 0;
	tab_len = 0;
	while (environ[tab_len] != NULL)
	{
		len = 0;
		while (environ[tab_len][len] != NULL)
			len++;		
		tab_len++;
		if (len > max_len)
			max_len = len;
		data->env = malloc(sizeof(char) * tab_len + 1);
		while (tab_len > 0)
			data->env[tab_len] = malloc(sizeof(char) * max_len + 1);
		while (environ[tab_len] != NULL)
		{
			while (environ[tab_len][len] != NULL)
				data->env[tab_len][max_len] = environ[tab_len][max_len++];
			tab_len++;
		}
	}
}
