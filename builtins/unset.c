/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:29:16 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/15 16:27:56 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	del_env(t_data *data, char *delete)
{
	int		i;
	int		j;
	int		var_i;
	int		tab_len;
	char	**dup_env;

	tab_len = 0;
	i = 0;
	j = 0;
	var_i = get_this_env(delete, data->env);
	if (var_i == -1)
		return (0);
	while (data->env[tab_len] != NULL)
		tab_len++;
	dup_env = malloc(sizeof(char *) * (tab_len));
	if (dup_env == NULL)
		return (3);
	dup_env[tab_len - 1] = NULL;
	while (i < tab_len)
	{
		if (i != var_i)
			dup_env[j++] = ft_strdup(data->env[i]);
		i++;
	}
	free_tab(data->env);
	data->env = dup_env;
	return (0);
}

int	unset(t_data *data, char **tab)
{
	int	i;
	int	ret;

	i = 1;
	while (tab[i] != NULL)
	{
		if (ft_strchr(tab[i], '='))
			i++;
		ret = del_env(data, tab[i]);
		if (ret == 3)
			return (put_error(ERR_MALLOC, NULL), 3);
		else if (ret == 1)
			return (1);
		i++;
	}
	return (0);
}
