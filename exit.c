/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:46:11 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 17:08:43 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	ft_exit(char *arg)
{
	clear_history();
	free(arg);
	exit(EXIT_FAILURE);
}

void 	ft_error()
{
	printf("error invalid command\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

int    check_error(t_data *data, int i)
{
    if(ft_strncmp(data->token[i].litteral[0], ";",2) == 0|| ft_strncmp(data->token[i].litteral[0], "\\", 2) == 0)
        return(ft_error(), -1);
    return(0);
}