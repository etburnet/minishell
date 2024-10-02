/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:43:04 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/02 13:38:39 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    check_arg(t_data *data, int i, e_type type)
{
    int j;
    
    j = 1;
    i++;
    while(i < data->lenght_token)
    {
        if((data->token[i - 1].type == type || data->token[i - 1].type == arg) && (data->token[i].type == word || data->token[i].type == string))
        {
            data->token[i].type = arg;
            data->token[i].nb_arg += 1;
            if(data->token[i].nb_arg > data->token[i].size - 1)
                data->token[i].litteral = my_realloc(data->token[i].litteral,data->token[i].size + 1);
            data->token[i].litteral[j] = ft_strdup(data->token[i].litteral[0]);
            j++;
            data->token[i].litteral[j] = NULL;
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
            data->token[i].type = command;
            data->token[i].full_path = ft_find_cmd(data->token[i].litteral);
            check_arg(data, i, command);
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
        if(data->token[i].type == greater || data->token[i].type == greatergreater)
        {
            if(i + 1 <= data->lenght_token && (data->token[i + 1].type == word || data->token[i + 1].type == string))
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
            if(i + 1 <= data->lenght_token && (data->token[i + 1].type == word || data->token[i + 1].type == string))
                data->token[i + 1].type = infile;
        }
        i++;
    }
}

// const char* gettypeName(enum e_type type) 
// {
//    switch (type) 
//    {
//       case undefine: return "undefine";
//       case string: return "string";
//       case word: return "word";
//     //   case number: return "number";
//       case less: return "less";
//       case greater: return "greater";
//       case greatergreater: return "greatergreater";
//       case here_doc: return "here_doc";
//       case exit_status: return "exit_status";
//       case pipes: return "pipes";
//       case infile: return "infile";
//       case outfile: return "outfile";
//       case variable: return "variable";
//       case command: return "command";
//       case arg: return "arg";
//       case built_in: return "built_in";
//    }
// }

void    is_built_in(t_data *data)
{
    int i;
    
    i = 0;
    if(strncmp(data->token[i].litteral[0], "echo", 5) == 0)
        data->token[i].type = built_in;
    else if(strncmp(data->token[i].litteral[0], "cd", 3) == 0)
        data->token[i].type = built_in;
    else if(strncmp(data->token[i].litteral[0], "pwd", 4) == 0)
        data->token[i].type = built_in;
    else if(strncmp(data->token[i].litteral[0], "export", 7) == 0)
        data->token[i].type = built_in;
    else if(strncmp(data->token[i].litteral[0], "unset", 6) == 0)
        data->token[i].type = built_in;
    else if(strncmp(data->token[i].litteral[0], "env", 4) == 0)
        data->token[i].type = built_in;
    else if(strncmp(data->token[i].litteral[0], "exit", 5) == 0)
        data->token[i].type = built_in;
    if(data->token[i].type == built_in)
        check_arg(data, i, built_in);
}

void    identify_command(t_data *data)
{
    is_built_in(data);
    check_infile(data);
    check_outfile(data);
    check_command(data);
    // int i = 0;
    // while(i < data->lenght_token)
	// {
	// 	printf("token %d type %s = %s\n path = %s\n", data->token[i].position, gettypeName(data->token[i].type), data->token[i].litteral[0], data->token[i].full_path);
	// 	i++;
	// }
}

