/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:52 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:22 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int	ft_atoi(const char *nptr)
// {
// 	int	i;
// 	int	sign;
// 	int	result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
// 		i++;
// 	while (nptr[i] == '-' || nptr[i] == '+')
// 	{
// 		if (nptr[i] == '-')
// 		{
// 			sign *= -1;
// 		}
// 		i++;
// 		if (nptr[i] == '-' || nptr[i] == '+')
// 			return (0);
// 	}
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		result = result * 10 + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (result * sign);
// }
// int	ft_isdigit(char *c)
// {
// 	int	i;

// 	i = 0;
// 	if (c[i] == '-' || c[i] == '+')
// 		i++;
// 	while (c[i] != '\0')
// 	{
// 		if (c[i] >= '0' && c[i] <= '9')
// 			i++;
// 		else
// 			return (0);
// 	}
// 	return (!0);
// }
// int    check_error(t_data *data, int i)
// {
//     if(ft_strncmp(data->token[i].litteral, ";",2) || ft_strncmp(data->token[i].litteral, "\\", 2))
//         return(ft_error(), -1);
//     return(0);
// }
// int   check_nb(t_data *data, int i)
// {
//     if(data->token[i].lexeme != undefine)
//         return(0);
//     if(ft_isdigit(data->token[i]) != 0)
//     {
//         data->token[i].value = ft_atoi(data->token[i].litteral);
//         data->token[i].lexeme = number;
//     }
//     return(0);
// }

// int    check_operator(t_data *data, int i)
// {
//     if(data->token[i].lexeme != undefine)
//         return(0);
//     if(ft_strncmp(data->token[i].litteral, "<", 2))
//         data->token[i].lexeme = less;
//     if(ft_strncmp(data->token[i].litteral, ">", 2))
//         data->token[i].lexeme = greater;
//     if(ft_strncmp(data->token[i].litteral, "<<", 3))
//         data->token[i].lexeme = here_doc;
//     if(ft_strncmp(data->token[i].litteral, ">>", 3))
//         data->token[i].lexeme = greatergreater;
//     if(ft_strncmp(data->token[i].litteral, "|", 2))
//         data->token[i].lexeme = pipes;   
//     if(ft_strncmp(data->token[i].litteral, "$?", 3))
//         data->token[i].lexeme = exit_status;  
//     return(0);
// }
// int    check_var_env(t_data *data, i)
// {
//     if(data->token[i].lexeme != undefine)
//         return(0);
//     if(ft_strncmp(data->token[i].litteral, '$', 2))
//     {
//         data->token[i].lexeme = var_env;//var = string en majuscule ? a check
//     }
//     return(0);
// }

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
        check_var_env(data, i);
        // check_command();
        // check_infile();
        // check_outfile();
        i++;
    }
    while(i < data->lenght_token)
	{
		printf("token %d pos %u = %s\n", data->token[i].position, data->token[i].lexeme, data->token[i].litteral);
		i++;
	}
    return(0);
}