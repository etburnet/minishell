/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:28:41 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/16 13:26:35 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	increment_shlvl(char **shlvl_cp, char *str)
{
	int	shlvl_value;

	*shlvl_cp = ft_strdup(str);
	if (*shlvl_cp == NULL)
		return (3);
	shlvl_value = ft_atoi(*shlvl_cp) + 1;
	ft_free(*shlvl_cp);
	*shlvl_cp = ft_itoa(shlvl_value);
	if (*shlvl_cp == NULL)
		return (3);
	return (0);
}

int	update_shlvl(t_data *data)
{
	char	*cat;
	int		shlvl;
	char	*shlvl_cp;

	shlvl_cp = NULL;
	shlvl = get_this_env("SHLVL", data->env);
	if (shlvl == -1)
		return (1);
	if (increment_shlvl(&shlvl_cp, &data->env[shlvl][6]) == 3)
		return (3);
	cat = malloc(sizeof(char) * ft_strlen(shlvl_cp) + 8);
	if (cat == NULL)
		return (ft_free(shlvl_cp), 3);
	cat[0] = '\0';
	if (shlvl == -1)
		return (ft_putstr_fd("Unable to find SHLVL", 2), 1);
	ft_strlcat(cat, "SHLVL=", 7);
	ft_strlcat(cat, shlvl_cp, ft_strlen(shlvl_cp) + 7);
	ft_free(data->env[shlvl]);
	data->env[shlvl] = ft_strdup(cat);
	ft_free(cat);
	ft_free(shlvl_cp);
	if (data->env[shlvl] == NULL)
		return (3);
	return (0);
}
