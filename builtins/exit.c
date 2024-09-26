/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:59:33 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/26 13:25:50 by eburnet          ###   ########.fr       */
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

void	ft_exit(t_data *data)
{
	long int	n;

	
	n = 214748364854;//ft_atoi(data->input[1]);

	ft_clean(data);
	exit(n);
}