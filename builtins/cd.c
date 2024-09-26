/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:13 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/26 15:12:49 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_this_env(char *var, char **env)
{
	int		i;
	int		len;

	len = ft_strlen(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, len) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (-1);
	return (i);
}

int	edit_old_pwd(t_data *data, char *cp_pwd)
{
	int	oldpwd;
	char *cat;
	
	cat = malloc(sizeof(char) * ft_strlen(cp_pwd) + 8);
	if (cat == NULL)
		return (ERR_MALLOC, 1);
	cat[0] = '\0';
	oldpwd = get_this_env("OLDPWD", data->env);
	if (oldpwd == -1)
		return (ft_putstr_fd("Unable to find OLDPWD", 2) ,1);
	ft_strlcat(cat, "OLDPWD=", 8);
	ft_strlcat(cat, cp_pwd, ft_strlen(cp_pwd) + 9);
	if (cat == NULL)
		return (ERR_MALLOC, 1);	
	free(data->env[oldpwd]);
	data->env[oldpwd] = ft_strdup(cat);
	free(cat);
	if (data->env[oldpwd] == NULL)
		return (ERR_MALLOC, 1);
	return (0);	
}

int	open_ch_dir(char *dir)
{
	DIR *stream_dir;

	stream_dir = opendir(dir);
	if (stream_dir == NULL)
		return (1);
	closedir(stream_dir);
	if (chdir(dir) == -1)
		return (1);
	return (0);
}

int	cd(t_data *data)
{
	char	cp_pwd[PATH_MAX];

	if (data->input[2] != NULL)
		return (ft_putstr_fd("Too much args\n", 2), 1);
	else
	{
		if (getcwd(cp_pwd, PATH_MAX))
		{
			if (open_ch_dir(data->input[1]) == 0)
				edit_old_pwd(data, cp_pwd);
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}
