/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:13 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/22 13:11:35 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_manage_pwd(t_data *data, int id_pwd, char **cat)
{
	if (id_pwd >= 0)
	{
		ft_free(data->cp_env[id_pwd]);
		data->cp_env[id_pwd] = *cat;
		if (!data->cp_env[id_pwd])
			return (put_error(ERR_MALLOC, NULL), 3);
	}
	else
	{
		if (dup_env(data, *cat) == 3)
			return (ft_free(*cat), put_error(ERR_MALLOC, NULL), 3);
		ft_free(*cat);
	}
	return (0);
}

int	edit_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	int		id_pwd;
	char	*cat;
	int		ret;

	id_pwd = get_this_env("PWD", data->cp_env);
	if (getcwd(buf, PATH_MAX))
	{
		cat = malloc(sizeof(char) * ft_strlen(buf) + 5);
		if (cat == NULL)
			return (put_error(ERR_MALLOC, NULL), 3);
		cat[0] = '\0';
		ft_strlcat(cat, "PWD=", 5);
		ft_strlcat(cat, buf, ft_strlen(buf) + 6);
		ret = ft_manage_pwd(data, id_pwd, &cat);
		if (ret != 0)
			return (ret);
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
		if (data->cp_env[oldpwd] == NULL)
			return (ft_free(cat), put_error(ERR_MALLOC, NULL), 3);
	}
	else if (dup_env(data, cat) == 3)
		return (ft_free(cat), put_error(ERR_MALLOC, NULL), 3);
	ft_free(cat);
	return (0);
}

int	ft_cd_traitement(t_data *data, int id_env, char *tab)
{
	int		ret;
	char	*cp_pwd;

	ret = 0;
	cp_pwd = ft_strdup(&data->cp_env[id_env][4]);
	if (cp_pwd == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	if (open_ch_dir(tab) == 1)
		return (free(cp_pwd), 1);
	ret = edit_old_pwd(data, cp_pwd);
	if (ret != 0)
		return (free(cp_pwd), ret);
	ret = edit_pwd(data);
	if (ret != 0)
		return (free(cp_pwd), ret);
	free(cp_pwd);
	return (0);
}

int	cd(t_data *data, char **tab)
{
	int	id_env;
	int	ret;

	ret = 0;
	if (tab[1] == NULL)
		return (cd_home(data));
	if (tab[2] != NULL && tab[1] != NULL)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	else
	{
		id_env = get_this_env("PWD", data->cp_env);
		if (id_env >= 0)
		{
			ret = ft_cd_traitement(data, id_env, tab[1]);
			if (ret != 0)
				return (ret);
		}
		else
			return (1);
	}
	return (0);
}
