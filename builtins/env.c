/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/07 17:30:40 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int		print_env(t_data *data)
int		print_env(t_data *data)
{
	int i;

	i = 0;
	if(data->env == NULL)
		return(1);
	while (data->env[i])
		printf("%s\n", data->env[i++]);
	return(0);
	return(0);
}

int	copy_env(t_data *data)
{
	int	tab_len;
	int	i;

	i = 0;
	tab_len = 0;
	if (environ == NULL || environ[i] == NULL)
		return (3);
	if (environ == NULL || environ[i] == NULL)
		return (3);
	while (environ[tab_len])
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

