/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:49:49 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/09 11:48:45 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data_token(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < data->lenght_token)
	{
		while (j < data->token[i].nb_arg)
		{
			free(data->token[i].litteral[j]);
			j++;
		}
		free(data->token[i].litteral);
		i++;
	}
	free(data->token);
	free(data->source);
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

int	check_error(t_data *data, int i)
{
	if (ft_strncmp(data->token[i].litteral[0], ";", 2) == 0
		|| ft_strncmp(data->token[i].litteral[0], "\\", 2) == 0)
		return (put_error("error invalid command", NULL), -1);
	return (0);
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
