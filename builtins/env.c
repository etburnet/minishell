/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:27:46 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/21 18:27:48 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	if (data->cp_env == NULL)
		return (1);
	while (data->cp_env[i])
	{
		len = ft_strlen(data->cp_env[i]);
		if (write(1, data->cp_env[i++], len) != len)
			return (perror("pwd: write error"), 1);
		if (write(1, "\n", 1) != 1)
			return (perror("pwd: write error"), 1);
	}
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
