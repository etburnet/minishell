/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:59:33 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/27 17:58:30 by eburnet          ###   ########.fr       */
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

	n = 0;
	clear_history();
	ft_clean(data);
	exit(n);
}

void	free_data_token(t_data *data)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(i < data->lenght_token)
	{
		while(j < data->token[i].nb_arg)
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

void 	ft_error()
{
	ft_putstr_fd("error invalid command\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}

int    check_error(t_data *data, int i)
{
    if(ft_strncmp(data->token[i].litteral[0], ";",2) == 0|| ft_strncmp(data->token[i].litteral[0], "\\", 2) == 0)
        return(ft_error(), -1);
    return(0);
}