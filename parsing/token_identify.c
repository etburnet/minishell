/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:52 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/04 16:53:12 by opdi-bia         ###   ########.fr       */
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

void    set_heredoc(t_data *data, int i)
{
    char *tmp;
    char *buffer;
    int fd;
   
    
    if(data->token[i].type == here_doc)
    {
        fd = open_file(data->token[i], 3);
        printf("fd = %i\n", fd);
        data->token[i + 1].type = delimiter;
        tmp = strdup(data->token[i + 1]. litteral[0]);
        while(strncmp(buffer, tmp, (strlen(tmp) + 1)) != 0)
        {
            buffer = readline(">");
		    write(fd, buffer, ft_strlen(buffer));
        }
        data->token[i].fd = fd;
    }
}

int    check_operator(t_data *data, int i)
{
    if(data->token[i].type != undefine)
        return(0);
    if(ft_strncmp(data->token[i].litteral[0], "<", 2) == 0)
        data->token[i].type = less;
    if(ft_strncmp(data->token[i].litteral[0], ">", 2) == 0)
        data->token[i].type = greater;
    if(ft_strncmp(data->token[i].litteral[0], "<<", 3) == 0)
    {
            data->token[i].type = here_doc;
            set_heredoc(data, i);
    }
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
