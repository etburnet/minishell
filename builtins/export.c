/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:35:56 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/30 16:12:41 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_ok(char *name)
{
	while (*name != '\0')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (1);
		name++;
	}
	return (0);
}

int	dup_env(t_data *data, char *new)
{
	int		tab_len;
	int		i;
	char	**dup_env;

	i = 0;
	tab_len = 0;
	while (data->env[tab_len] != 0)
		tab_len++;
	dup_env = malloc(sizeof(char *) * (tab_len + 2));
	if (dup_env == NULL)
		return (3);
	dup_env[tab_len + 1] = NULL;
	while (data->env[i] != NULL)
	{
		dup_env[i] = ft_strdup(data->env[i]);
		if (dup_env[i] == NULL)
			return (free_tab(dup_env), 3);
		i++;
	}
	dup_env[tab_len] = ft_strdup(new);
	free_tab(data->env);
	data->env = dup_env;
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
	if (dup_env(data, cat) == 3)
		return (free(cat), 3);
	free(cat);
	return (0);
}

int	export_parsing(t_data *data, int i, char **tab)
{	
	int		j;
	int		len;
	int		val;
	char	*name;
	char	*value;

	val = 1;
	len = ft_strlen(tab[i]);
	j = 0;
	while (tab[i][j] != '=' && tab[i][j])
		j++;
	if (j == len && tab[i][j] != '=')
		return (0);
	if (j == len && tab[i][j] == '=')
		j--;
	else
	{
		j--;
		value = malloc(sizeof(char) * (len - j + 1));
		if (value == NULL)
			return (3);
	}
	name = malloc(sizeof(char) * (j + 2));
	if (name == NULL)
		return (free(name), 3);
	ft_strlcpy(name, tab[i], j + 2);
	ft_strlcpy(value, &tab[i][j + 2], len - (j + 1));
	//printf("%s, %s\n", name, value);
	if (is_var_ok(name) == 0)
	{
		if (add_env_var(name, value, data) == 3)
		{
			if (value != NULL)
				free(value);
			return (free(name), 3);
		}
	}
	else
	{
		put_error("export: not valid in this context: ", name);
		if (value != NULL)
			free(value);
		return (free(name), 1);
	}
	if (value != NULL)
		free(value);
	free(name);
	return (0);
}

int	export(t_data *data, char **tab)
{
	int	i;
	int	ret;
	
	i = 1;
	while (tab[i] != NULL)
	{
		ret = export_parsing(data, i, tab);
		if (ret == 3)
			return (ERR_MALLOC, 3);
		else if (ret == 1)
			return (1);
		i++;
	}
	return (0);
}
