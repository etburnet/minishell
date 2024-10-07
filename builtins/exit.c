/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:59:33 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/07 17:31:06 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_clean(t_data *data)
{
	clear_history();
	if (data->arg != NULL)
		free(data->arg);
	if (data->env != NULL)
		free_tab(data->env);
/* 	if (data->input != NULL)
		free_tab(data->input); */
}

int	ft_check_str(char *str)
{
	int	i;
	int	isnegative;

	isnegative = 1;
	int	i;
	int	isnegative;

	isnegative = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	else
	{
		while (ft_isdigit(str[i]))
			i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	else
	{
		while (ft_isdigit(str[i]))
			i++;
	}
	free(data->token);
	free(data->source);
}

void 	ft_error()
{
	ft_putstr_fd("error invalid command\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	ft_exit(t_data *data, char **tab, int n)
int	ft_exit(t_data *data, char **tab, int n)
{
	if ((tab == NULL && n == 0))
		n = 0;
	else if (tab != NULL && tab[0] != NULL && tab[1] == NULL)
		n = 0;
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
	clear_history();
	ft_clean(data);
	exit(n);
	return (1);
	if ((tab == NULL && n == 0))
		n = 0;
	else if (tab != NULL && tab[0] != NULL && tab[1] == NULL)
		n = 0;
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
	clear_history();
	ft_clean(data);
	exit(n);
	return (1);
}

