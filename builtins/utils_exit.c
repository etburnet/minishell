/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:49:49 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/16 15:23:03 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data_token(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if(data->source_lenght < 0 || !data->token || !data->source)
		return ;
	while (i < data->lenght_token)
	{
		if (!data->token[i].tab)
			return ;
		while (j <= data->token[i].nb_arg)
		{
			ft_free(data->token[i].tab[j]);
			j++;
		}
		if (data->token[i].full_path)
			ft_free(data->token[i].full_path);
		if (data->token[i].tab)
			free(data->token[i].tab);
		ft_close(data, data->token[i].fdin, data->token[i].fdout);
		i++;
		j = 0;
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
