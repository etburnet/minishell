/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:29:16 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/04 16:09:14 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	del_env(t_data *data, char *delete)
{
	int		i[3];
	int		tab_len;
	char	**dup_env;

	tab_len = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = get_this_env(delete, data->cp_env);
	if (i[2] < 0)
		return (0);
	while (data->cp_env[tab_len] != NULL)
		tab_len++;
	dup_env = malloc(sizeof(char *) * (tab_len));
	if (dup_env == NULL)
		return (3);
	dup_env[tab_len - 1] = NULL;
	while (i[0] < tab_len)
	{
		if (i[0] != i[2])
			dup_env[i[1]++] = ft_strdup(data->cp_env[i[0]]);
		i[0]++;
	}
	ft_free_tab(data->cp_env);
	data->cp_env = dup_env;
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
			return (0);
		ret = del_env(data, tab[i]);
		if (ret == 3)
			return (put_error(ERR_MALLOC, NULL), 3);
		else if (ret == 1)
			return (1);
		i++;
	}
	return (0);
}
