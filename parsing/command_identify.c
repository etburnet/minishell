/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:43:04 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/30 13:20:16 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
            data->token[i].nb_arg += 1;
            if(data->token[i].nb_arg > data->token[i].size)
                data->token[i].litteral = my_realloc(data->token[i].litteral,data->token[i].size);
            data->token[i].litteral[j] = ft_strdup(data->token[i].litteral[0]);
            j++;
        }
        i++;
    }
}

int    check_command(t_data *data)
{
    int i;

    i = 0;
    while(i < data->lenght_token)
    {
        if(data->token[i].type == word || data->token[i].type == string)
        {
            data->token[i].full_path = ft_find_cmd(data->token[i].litteral);
            if(data->token[i].full_path != NULL)
            {
                data->token[i].type = command;
                check_arg(data, i);
            }
        }
        i++;
    }
    return(0);
}

void    check_outfile(t_data *data)
{
    int i = 0;

    while(i < data->lenght_token)
    {
        if(data->token[i].type == greater)
        {
            if(i > 0 && (data->token[i + 1].type == word || data->token[i + 1].type == string))
                data->token[i + 1].type = outfile;
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
const char* gettypeName(enum e_type type) 
{
   switch (type) 
   {
      case undefine: return "undefine";
      case string: return "string";
      case word: return "word";
      case number: return "number";
      case less: return "less";
      case greater: return "greater";
      case greatergreater: return "greatergreater";
      case here_doc: return "here_doc";
      case exit_status: return "exit_status";
      case pipes: return "pipes";
      case infile: return "infile";
      case outfile: return "outfile";
      case variable: return "variable";
      case command: return "command";
      case arg: return "arg";
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
		printf("token %d type %s = %s\n path = %s\n", data->token[i].position, gettypeName(data->token[i].type), data->token[i].litteral[0], data->token[i].full_path);
		i++;
	}
}




//  int i = 0;
//     while(i < data->lenght_token)
// 	{
// 		printf("token %d type %s = %s\n path = %s\n", data->token[i].position, gettypeName(data->token[i].type), data->token[i].litteral[0], data->token[i].full_path);
// 		i++;
// 	}