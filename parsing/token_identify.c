/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:52 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/08 16:49:11 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
            data->token[i + 1].type = delimiter;
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
// char    *remove_quote(char *string)
// {
//     int i;

//     i = 0;
//     while(s[i] == ' ')
// 		data->cur++;
// 	data->start = data->cur;
// 	if (s[i] != ' ' && s[i] != '\0')
// 	{
// 		while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
// 			data->cur++;;
// 		data->cur = check_quote(s, data->cur, '\'');
// 		if(data->cur == -1)
// 			return(put_error("error invalid command", NULL), -1);
// 		data->cur = check_quote(s, data->cur, '\"');
// 		if(data->cur == -1)
// 			return(put_error("error invalid command", NULL), -1);
// 		while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
// 			data->cur++;;
// 		if(s[i] == ' ' || s[i] == '\0')
// 			i = tokenise(data, i);
// 	}
// }

int     check_string(t_data *data , int i)
{
    if(data->token[i].type != undefine)
        return(0);
    if(ft_strchr(data->token[i].litteral[0], '\'') != 0 || ft_strchr(data->token[i].litteral[0], '\"') != 0)
    {
       data->token[i].type = string;
    //    data->token[i].litteral[0] = remove_quote(data->token[i].litteral[0]);
    }
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
        check_operator(data, i);
        check_var(data, i);
        check_string(data, i);
        if(data->token[i].type == undefine)
            data->token[i].type = word;
        i++;
    }
	return(0);
}
