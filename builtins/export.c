/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:35:56 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/22 13:06:27 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup_env(t_data *data, char *new)
{
	int		tab_len;
	int		i;
	char	**dup_env;

	i = 0;
	tab_len = 0;
	while (data->cp_env[tab_len] != 0)
		tab_len++;
	dup_env = malloc(sizeof(char *) * (tab_len + 2));
	if (dup_env == NULL)
		return (3);
	dup_env[tab_len + 1] = NULL;
	while (data->cp_env[i] != NULL)
	{
		dup_env[i] = ft_strdup(data->cp_env[i]);
		if (dup_env[i] == NULL)
			return (free_tab(dup_env), 3);
		i++;
	}
	dup_env[tab_len] = ft_strdup(new);
	free_tab(data->cp_env);
	data->cp_env = dup_env;
	return (0);
}

int	add_env_var(char *name, char *value, t_data *data)
{
	char	*cat;

	cat = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (cat == NULL)
		return (3);
	cat[0] = '\0';
	ft_strlcat(cat, name, ft_strlen(name) + 1);
	if (value != NULL)
	{
		ft_strlcat(cat, "=", ft_strlen(name) + 2);
		ft_strlcat(cat, value, ft_strlen(name) + ft_strlen(value) + 2);
	}
	if (add_or_update(data, name, &cat) == 3)
		return (3);
	ft_free(cat);
	return (0);
}

int	init_export(char *str, int *j, int len, char **value)
{
	if (str[0] == '=')
		return (put_error(ERR_IDE, str), 1);
	while (str[*j] != '=' && str[*j])
		(*j)++;
	if (*j == len && str[*j] != '=')
	{
		if (is_var_ok(str) == 1)
			return (put_error(ERR_IDE, str), 1);
		return (-1);
	}
	else if (*j == len && str[*j] == '=')
		(*j)--;
	else
	{
		(*j)--;
		*value = malloc(sizeof(char) * (len - *j + 1));
		if (*value == NULL)
			return (3);
	}
	return (0);
}

int	export_parsing(t_data *data, char *str, int len, int j)
{
	int		ret;
	char	*name;
	char	*value;

	ret = 0;
	ret = init_export(str, &j, len, &value);
	if (ret == -1)
		return (0);
	if (ret != 0)
		return (ret);
	name = malloc(sizeof(char) * (j + 2));
	if (name == NULL)
		return (ft_free(name), 3);
	ft_strlcpy(name, str, j + 2);
	ft_strlcpy(value, &str[j + 2], len - (j + 1));
	if (is_var_ok(name) == 0)
	{
		ret = add_env_var(name, value, data);
		if (ret != 0)
			return (ft_free(value), ft_free(name), ret);
	}
	else
		return (put_error(ERR_CONT, name), ft_free(value), ft_free(name), 1);
	return (ft_free(value), ft_free(name), 0);
}

int	export(t_data *data, char **tab)
{
	int	i;
	int	ret;
	int	len;

	i = 1;
	while (tab[i] != NULL)
	{
		len = ft_strlen(tab[i]);
		ret = export_parsing(data, tab[i], len, 0);
		if (ret == 3)
			return (put_error(ERR_MALLOC, NULL), 3);
		else if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
