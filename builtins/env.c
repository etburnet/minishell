/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/17 11:24:53 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->env == NULL)
		return (1);
	while (data->env[i])
		printf("%s\n", data->env[i++]);
	return (0);
}

int	copy_env(t_data *data, char **environ)
{
	int	tab_len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	tab_len = 0;
	if (environ == NULL || environ[0] == NULL)
		return (put_error("Env not found", NULL), 1);
	while (environ[tab_len])
		tab_len++;
	data->env = malloc(sizeof(char *) * (tab_len + 1));
	if (data->env == NULL)
		return (3);
	while (j <= tab_len)
		data->env[j++] = NULL;
	while (i < tab_len)
	{
		data->env[i] = ft_strdup(environ[i]);
		if (data->env[i] == NULL)
			return (put_error(ERR_MALLOC, NULL), 3);
		i++;
	}
	return (0);
}
