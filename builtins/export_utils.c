/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:21:16 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/21 18:28:16 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_ok(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (1);
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	add_or_update(t_data *data, char *name, char **cat)
{
	int	env_id;

	env_id = get_this_env(name, data->cp_env);
	if (env_id == -1)
	{
		if (dup_env(data, *cat) == 3)
			return (ft_free(*cat), 3);
	}
	else
	{
		if (del_env(data, name) == 3)
			return (ft_free(*cat), put_error(ERR_MALLOC, NULL), 3);
		if (dup_env(data, *cat) == 3)
			return (ft_free(*cat), 3);
	}
	return (0);
}
