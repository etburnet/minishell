/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:49:49 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/22 12:29:37 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data_token(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (data->source_lenght < 0 || !data->token || !data->source)
		return ;
	while (i < data->lenght_token)
	{
		j = 0;
		if (!data->token[i].tab)
			return ;
		while (j <= data->token[i].nb_arg)
			ft_free(data->token[i].tab[j++]);
		ft_free(data->token[i].full_path);
		if (data->token[i].tab)
			free(data->token[i].tab);
		ft_close(data, data->token[i].fdin, data->token[i].fdout);
		i++;
	}
	ft_close(data, data->pipe_fd[0], data->pipe_fd[1]);
	ft_close(data, data->old_pipe[0], data->old_pipe[1]);
	if (data->token)
		free(data->token);
	ft_free(data->source);
}

int	ft_err_exit(t_data *data, char *err_msg, int n)
{
	put_error(err_msg, NULL);
	if (n == 2)
	{
		clear_history();
		ft_clean(data);
		exit(n);
	}
	return (n);
}

long int	ft_atol(const char *nptr)
{
	char		*str;
	int			i;
	int			isnegative;
	long int	result;

	str = (char *)nptr;
	i = 0;
	isnegative = 1;
	result = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			isnegative *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * isnegative);
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

int	cd_home(t_data *data)
{
	DIR			*stream_dir;
	struct stat	path_stat;
	char	*dir;
	int		home_id;

	home_id = get_this_env("HOME", data->cp_env);
	if (home_id == -1)
		return (1);
	dir = ft_strdup(&data->cp_env[home_id][5]);
	if (dir == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	if (stat(dir, &path_stat) != 0)
		return (free(dir), perror(dir), 1);
	if (S_ISDIR(path_stat.st_mode))
	{
		stream_dir = opendir(dir);
		if (stream_dir == NULL)
			return (free(dir), put_error("No such file or directory: ", dir), 1);
		closedir(stream_dir);
		if (chdir(dir) == -1)
			return (free(dir), 1);
		return (free(dir), 0);
	}
	return (free(dir), put_error("Not a directory: ", dir), 1);
}
