/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:52 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/30 14:34:27 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int   check_nb(t_data *data, int i)
// {
//     if(data->token[i].type != undefine)
//         return(0);
//     if(ft_isdigit_edit(data->token[i].litteral[0]) != 0)
//     {
//         data->token[i].value = ft_atoi(data->token[i].litteral[0]);
//         data->token[i].type = number;
//     }
//     return(0);
// }

int    check_operator(t_data *data, int i)
{
    if(data->token[i].type != undefine)
        return(0);
    if(ft_strncmp(data->token[i].litteral[0], "<", 2) == 0)
        data->token[i].type = less;
    if(ft_strncmp(data->token[i].litteral[0], ">", 2) == 0)
        data->token[i].type = greater;
    if(ft_strncmp(data->token[i].litteral[0], "<<", 3) == 0)
        data->token[i].type = here_doc;
    if(ft_strncmp(data->token[i].litteral[0], ">>", 3) == 0)
        data->token[i].type = greatergreater;
    if(ft_strncmp(data->token[i].litteral[0], "|", 2) == 0)
        data->token[i].type = pipes;   
    if(ft_strncmp(data->token[i].litteral[0], "$?", 3) == 0)
        data->token[i].type = exit_status;  
    return(0);
}

int    check_var(t_data *data, int i)
{
    if(data->token[i].type != undefine)
        return(0);
    if(ft_strncmp(data->token[i].litteral[0], "$", 1) == 0)
        data->token[i].type = variable;
    return(0);
}

int     check_string(t_data *data , int i)
{
    if(data->token[i].type != undefine)
        return(0);
    if(ft_strchr(data->token[i].litteral[0], '\'') != 0 || ft_strchr(data->token[i].litteral[0], '\'') != 0)
       data->token[i].type = string;
    return(0);
}

int    identify_token(t_data *data)
{
    int i;

    i = 0;
    while(i < data->lenght_token)
    {
        if(check_error(data, i) != 0)
            return(-1);
        // check_nb(data, i);
        check_operator(data, i);
        check_var(data, i);
        check_string(data, i);
        if(data->token[i].type == undefine)
            data->token[i].type = word;
        i++;
    }
	return(0);
}
