/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:52 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/10 13:49:27 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator(t_data *data, int i)
{
	if (data->token[i].type != undefine)
		return (0);
	if (ft_strncmp(data->token[i].litteral[0], "<", 2) == 0)
		data->token[i].type = less;
	if (ft_strncmp(data->token[i].litteral[0], ">", 2) == 0)
		data->token[i].type = greater;
	if (ft_strncmp(data->token[i].litteral[0], "<<", 3) == 0)
	{
		data->token[i].type = here_doc;
		data->token[i + 1].type = delimiter;
	}
	if (ft_strncmp(data->token[i].litteral[0], ">>", 3) == 0)
		data->token[i].type = greatergreater;
	if (ft_strncmp(data->token[i].litteral[0], "|", 2) == 0)
		data->token[i].type = pipes;
	return (0);
}

int	check_var(t_data *data, int i)
{
	int	j;
	int	start;
	int	full_len;

	full_len = ft_strlen(data->token[i].litteral[0]);
	j = 0;
	if (data->token[i].type != undefine)
		return (0);
	while (data->token[i].litteral[0][j])
	{
		if (data->token[i].litteral[0][j] == '$')
		{
			j++;
			start = j;
			if (data->token[i].litteral[0][j] == '?')
				j = start;
			else
				while (ft_isalnum(data->token[i].litteral[0][j]) || data->token[i].litteral[0][j] == '_')
					j++;
			if (expand(data, i, start, j - start, full_len) == 3)
				return (put_error(ERR_MALLOC, NULL), 3);
		}
		else
			j++;
	}
	return (0);
}


int	check_string(t_data *data, int i)
{
    if(data->token[i].type != undefine)
        return(0);
    if(ft_strchr(data->token[i].litteral[0], '\'') != 0 || ft_strchr(data->token[i].litteral[0], '\"') != 0)
    {
       data->token[i].type = string;
       data->token[i].litteral[0] = remove_quote(data->token[i].litteral[0], 0, 0);
       if(data->token[i].litteral[0] == NULL)
        return(put_error(ERR_MALLOC, data->token[i].litteral[0]), 3);
    }
    return(0);
}

int	identify_token(t_data *data)
{
	int	i;

    i = 0;
    while(i < data->lenght_token)
    {
        check_operator(data, i);
        if(check_var(data, i) == 3)
			return(3);
        if(check_string(data, i) == 3)
            return (3);
        if(data->token[i].type == undefine)
            data->token[i].type = word;
        i++;
    }
	return(0);
}
