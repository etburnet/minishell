/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:13 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/18 14:09:02 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	edit_pwd(t_data *data)
{
	char 	buf[PATH_MAX];
	int		id_pwd;
	
	id_pwd = get_this_env("PWD", data->env);
	if (id_pwd == -1)
		return (ft_putstr_fd("Unable to find PWD", 2), 1);
	if (getcwd(buf, PATH_MAX))
	{
		free(data->env[id_pwd]);
		printf("%s\n", buf);
		data->env[id_pwd] = ft_strdup(buf);
		if (!data->env[id_pwd])
			return (put_error(ERR_MALLOC, NULL), 3);
	}
	else
		return (1);
	return (0);
}

int	edit_old_pwd(t_data *data, char *cp_pwd)
{
	int		oldpwd;
	char	*cat;

	cat = malloc(sizeof(char) * ft_strlen(cp_pwd) + 8);
	if (cat == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	cat[0] = '\0';
	if (data->env == NULL || data->env[0] == NULL)
		return (put_error("Env not found", NULL), 1);
	oldpwd = get_this_env("OLDPWD", data->env);
	if (oldpwd == -1)
		return (ft_putstr_fd("Unable to find OLDPWD", 2), 1);
	ft_strlcat(cat, "OLDPWD=", 8);
	ft_strlcat(cat, cp_pwd, ft_strlen(cp_pwd) + 9);
	ft_free(data->env[oldpwd]);
	data->env[oldpwd] = ft_strdup(cat);
	ft_free(cat);
	if (data->env[oldpwd] == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	return (0);
}

int	open_ch_dir(char *dir)
{
	DIR			*stream_dir;
	struct stat	path_stat;

	if (dir[0] == '\0')
		return (1);
	if (stat(dir, &path_stat) != 0)
		return (perror(dir), 1);
	if (S_ISREG(path_stat.st_mode))
		return (put_error("Not a directory: ", dir), 1);
	else if (S_ISDIR(path_stat.st_mode))
	{
		stream_dir = opendir(dir);
		if (stream_dir == NULL)
			return (put_error("No such file or directory: ", dir), 1);
		closedir(stream_dir);
		if (chdir(dir) == -1)
			return (1);
		return (0);
	}
	return (1);
}

int	cd(t_data *data, char **tab)
{
	char	*cp_pwd;
	int		id_env;
	int		ret;

	ret = 0;
	if (tab[1] == NULL)
		return (0);
	if (tab[2] != NULL && tab[1] != NULL)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	else
	{
		id_env = get_this_env("PWD", data->env);
		if (id_env > 0)
		{
			cp_pwd = ft_strdup(&data->env[id_env][4]);
			if (cp_pwd == NULL)
				return (put_error(ERR_MALLOC, NULL), 3);
			if (open_ch_dir(tab[1]) == 1)
				return (free(cp_pwd), 1);
			ret = edit_old_pwd(data, cp_pwd);
			if (ret != 0)
				return (ret);
			ret = edit_pwd(data);
			if (ret != 0)
				return (ret);
			free(cp_pwd);
		}
		else
			return (1);
	}
	return (0);
}
