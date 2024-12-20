/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:59:33 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/04 16:09:20 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean(t_data *data)
{
	clear_history();
	if (data->arg != NULL)
	{
		free_data_token(data);
		ft_free(data->arg);
	}
	if (data->cp_env != NULL)
		ft_free_tab(data->cp_env);
	free(data);
}

int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	else
	{
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] != '\0' && !ft_isdigit(str[i]))
		return (1);
	return (0);
}

int	ft_long_check(char *str)
{
	const char	*long_max_str;
	const char	*long_min_str;

	long_max_str = "9223372036854775807";
	long_min_str = "-9223372036854775808";
	if (str[0] == '-')
	{
		if (ft_strlen(str) > ft_strlen(long_min_str))
			return (1);
		else if (ft_strlen(str) == ft_strlen(long_min_str) && ft_strncmp(str,
				long_min_str, ft_strlen(str)) > 0)
			return (1);
	}
	else
	{
		if (ft_strlen(str) > ft_strlen(long_max_str))
			return (1);
		else if (ft_strlen(str) == ft_strlen(long_max_str) && ft_strncmp(str,
				long_max_str, ft_strlen(str)) > 0)
			return (1);
	}
	return (0);
}

int	ft_exit(t_data *data, char **tab, int n, int is_pipe)
{
	if (is_pipe == 0)
		ft_putstr_fd("exit\n", 1);
	if (tab != NULL && tab[0] != NULL && tab[1] == NULL)
		n = data->status;
	else if (tab != NULL)
	{
		if (tab[2] != NULL && ft_check_str(tab[1]) == 0)
			return (ft_err_exit(data, "too many arguments", 1));
		else if (tab[2] != NULL && ft_check_str(tab[1]) == 1)
			return (ft_err_exit(data, "numeric argument required", 2));
		else if (tab[2] == NULL && ft_check_str(tab[1]) == 1)
			return (ft_err_exit(data, "numeric argument required", 2));
		else if (tab[2] == NULL && ft_long_check(tab[1]) == 1)
			return (ft_err_exit(data, "numeric argument required", 2));
		else
			n = ft_atol(tab[1]) % 256;
	}
	ft_clean(data);
	exit(n);
	return (1);
}
