/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:13 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/19 19:03:04 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	edit_pwd(t_data *data)
{
	char 	buf[PATH_MAX];
	int		id_pwd;
	char	*cat;
	
	id_pwd = get_this_env("PWD", data->cp_env);
	if (getcwd(buf, PATH_MAX))
	{
		cat = malloc(sizeof(char) * ft_strlen(buf) + 5);
		if (cat == NULL)
			return (put_error(ERR_MALLOC, NULL), 3);
		cat[0] = '\0';
		ft_strlcat(cat, "PWD=", 5);
		ft_strlcat(cat, buf, ft_strlen(buf) + 6);
		//printf("cat %s\n", cat);
		if (id_pwd >= 0)
		{
			ft_free(data->cp_env[id_pwd]);
			data->cp_env[id_pwd] = cat;
			if (!data->cp_env[id_pwd])
				return (put_error(ERR_MALLOC, NULL), 3);
		}
		else
		{
			if (dup_env(data, cat) == 3)
				return (ft_free(cat), put_error(ERR_MALLOC, NULL), 3);
			ft_free(cat);
		}
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
	if (data->cp_env == NULL || data->cp_env[0] == NULL)
		return (put_error("Env not found", NULL), 1);
	oldpwd = get_this_env("OLDPWD", data->cp_env);
	ft_strlcat(cat, "OLDPWD=", 8);
	ft_strlcat(cat, cp_pwd, ft_strlen(cp_pwd) + 9);
	if (oldpwd != -1)
	{
		ft_free(data->cp_env[oldpwd]);
		data->cp_env[oldpwd] = ft_strdup(cat);
		ft_free(cat);
		if (data->cp_env[oldpwd] == NULL)
			return (put_error(ERR_MALLOC, NULL), 3);
	}
	else
	{
		if (dup_env(data, cat) == 3)
			return (ft_free(cat), put_error(ERR_MALLOC, NULL), 3);
		ft_free(cat);
	}
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
		id_env = get_this_env("PWD", data->cp_env);
		if (id_env >= 0)
		{
			cp_pwd = ft_strdup(&data->cp_env[id_env][4]);
			if (cp_pwd == NULL)
				return (put_error(ERR_MALLOC, NULL), 3);
			if (open_ch_dir(tab[1]) == 1)
				return (free(cp_pwd), 1);
			ret = edit_old_pwd(data, cp_pwd);
			if (ret != 0)
				return (free(cp_pwd), ret);
			ret = edit_pwd(data);
			if (ret != 0)
				return (free(cp_pwd), ret);
			free(cp_pwd);
		}
		else
			return (1);
	}
	return (0);
}
