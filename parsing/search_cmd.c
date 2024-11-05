/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:00:07 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/11/05 14:53:19 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_extract_path(t_data *data)
{
	char	*path;
	char	*trimmed;
	char	**splited;
	int		path_id;

	if (data->cp_env == NULL || data->cp_env[0] == NULL)
		return (put_error("Env not found", NULL), NULL);
	path_id = get_this_env("PATH", data->cp_env);
	if (path_id == -1)
		return (NULL);
	path = ft_strdup(data->cp_env[path_id]);
	if (path == NULL)
		return (NULL);
	trimmed = ft_strtrim(path, "PATH=");
	ft_free(path);
	if (trimmed == NULL)
		return (NULL);
	splited = ft_split(trimmed, ':');
	ft_free(trimmed);
	if (splited == NULL)
		return (NULL);
	return (splited);
}

char	*ft_cmd_path(char **path, char *full_path, char **cmd_tab)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		full_path = malloc(sizeof(char) * (ft_strlen(path[i])
					+ ft_strlen(cmd_tab[0]) + 2));
		if (full_path == NULL)
			return (ft_free_tab(path), NULL);
		full_path[0] = '\0';
		ft_strlcat(full_path, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(full_path)
			+ ft_strlen(cmd_tab[0]) + 1);
		if (access(full_path, X_OK) == 0)
			break ;
		ft_free(full_path);
		full_path = NULL;
		i++;
	}
	if (full_path == NULL)
		ft_free_tab(path);
	return (full_path);
}

char	*ft_find_cmd(t_data *data, char **cmd_tab)
{
	char	**path;
	char	*full_path;

	full_path = NULL;
	path = NULL;
	if (cmd_tab[0] == NULL)
		return (ft_free_tab(path), NULL);
	if (access(cmd_tab[0], X_OK) == 0)
	{
		full_path = malloc(sizeof(char) * ft_strlen(cmd_tab[0]) + 1);
		if (full_path == NULL)
			return (NULL);
		full_path[0] = '\0';
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(cmd_tab[0]) + 1);
		return (full_path);
	}
	path = ft_extract_path(data);
	if (path == NULL)
		return (NULL);
	full_path = ft_cmd_path(path, full_path, cmd_tab);
	if (full_path == NULL)
		return (NULL);
	ft_free_tab(path);
	return (full_path);
}
