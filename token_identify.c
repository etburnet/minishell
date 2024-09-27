/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:52 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 14:45:55 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   check_nb(t_data *data, int i)
{
    if(data->token[i].lexeme != undefine)
        return(0);
    if(ft_isdigit(data->token[i].litteral) != 0)
    {
        data->token[i].value = ft_atoi(data->token[i].litteral);
        data->token[i].lexeme = number;
    }
    return(0);
}

int    check_operator(t_data *data, int i)
{
    if(data->token[i].lexeme != undefine)
        return(0);
    if(ft_strncmp(data->token[i].litteral, "<", 2) == 0)
        data->token[i].lexeme = less;
    if(ft_strncmp(data->token[i].litteral, ">", 2) == 0)
        data->token[i].lexeme = greater;
    if(ft_strncmp(data->token[i].litteral, "<<", 3) == 0)
        data->token[i].lexeme = here_doc;
    if(ft_strncmp(data->token[i].litteral, ">>", 3) == 0)
        data->token[i].lexeme = greatergreater;
    if(ft_strncmp(data->token[i].litteral, "|", 2) == 0)
        data->token[i].lexeme = pipes;   
    if(ft_strncmp(data->token[i].litteral, "$?", 3) == 0)
        data->token[i].lexeme = exit_status;  
    return(0);
}

int    check_var(t_data *data, int i)
{
    if(data->token[i].lexeme != undefine)
        return(0);
    if(ft_strncmp(data->token[i].litteral, "$", 1) == 0)
        data->token[i].lexeme = var;
    return(0);
}

int     check_string(t_data *data , int i)
{
    if(data->token[i].lexeme != undefine)
        return(0);
    if(ft_strchr(data->token[i].litteral, "\'") != 0 || ft_strchr(data->token[i].litteral, "\'") != 0)
       data->token[i].lexeme = string;
}

int    identify_token(t_data *data)
{
    int i;

    i = 0;
    while(i < data->lenght_token)
    {
        if(check_error(data, i) != 0)
            return(-1);
        check_nb(data, i);
        check_operator(data, i);
        check_var(data, i);
        check_string(data, i);
        if(data->token[i].lexeme == undefine)
            data->token[i].lexeme = word;
        i++;
    }
    return(0);
}
