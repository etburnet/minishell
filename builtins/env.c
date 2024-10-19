/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/18 12:04:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->cp_env == NULL)
		return (1);
	while (data->cp_env[i])
		printf("%s\n", data->cp_env[i++]);
	return (0);
}

int	copy_env(t_data *data, char **env)
{
	int	tab_len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	tab_len = 0;
	while (env[tab_len])
		tab_len++;
	data->cp_env = malloc(sizeof(char *) * (tab_len + 1));
	if (data->cp_env == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	while (j <= tab_len)
		data->cp_env[j++] = NULL;
	while (i < tab_len)
	{
		data->cp_env[i] = ft_strdup(env[i]);
		if (data->cp_env[i] == NULL)
			return (free_tab(data->cp_env), put_error(ERR_MALLOC, NULL), 3);
		i++;
	}
	if (tab_len == 0)
		return (1);
	return (0);
}
