/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:43:04 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 19:43:17 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>

void    check_arg(t_data *data, int i)
{
    int j;
    
    j = 1;
    i++;
    while(i < data->lenght_token)
    {
        if((data->token[i - 1].type == command || data->token[i - 1].type == arg) && (data->token[i].type == word || data->token[i].type == string))
        {
            data->token[i].type = arg;
            data->token[i].litteral[j] = ft_strdup(data->token[i].litteral[0]);
            data->token[i].nb_arg += 1;
            j++;
        }
        i++;
    }
}

void    check_command(t_data *data)
{
    int i;

    i = 0;
    while(i < data->lenght_token)
    {
        if(data->token[i].type == word || data->token[i].type == string)
        {
            // printf("ici %d\n", access(data->token[i].litteral[0], X_OK));
            // int err = errno;
            // fprintf(stderr, "Erreur : %s\n", strerror(err));
            if(access(data->token[i].litteral[0], X_OK) == 0)
            {
                data->token[i].type = command;
                check_arg(data, i);
            }
        }
        i++;
    }
}

void    check_outfile(t_data *data)
{
    int i = 0;

    while(i < data->lenght_token)
    {
        if(data->token[i].type == greater)
        {
            if(i > 0 && (data->token[i - 1].type == word || data->token[i - 1].type == string))
                data->token[i - 1].type = outfile;
        }
        i++;
    }
}

void    check_infile(t_data *data)
{
    int i = 0;

    while(i < data->lenght_token)
    {
        if(data->token[i].type == less)
        {
            if(i > 0 && (data->token[i - 1].type == word || data->token[i - 1].type == string))
                data->token[i - 1].type = infile;
        }
        i++;
    }
}

void    identify_command(t_data *data)
{
    check_infile(data);
    check_outfile(data);
    check_command(data);
    int i = 0;
    while(i < data->lenght_token)
	{
		printf("token %d type %d = %s\n", data->token[i].position, data->token[i].type, data->token[i].litteral[0]);
		i++;
	}
}

