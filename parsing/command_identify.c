/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:43:04 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/08 16:20:23 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    set_heredoc(t_data *data)
{
    char *buffer; 
    int cmd;
    int i; 
    int new;
	
    i = 0;
    init_signal_handler(2);
    while(i < data->lenght_token)
    {
        if(data->token[i].type == here_doc)
        {
		    new = dup(0);
            cmd = search_cmd(data, i);
            data->token[cmd].fdin = open_file(data->token[i], 3);
            buffer = readline(">");
            while(buffer != NULL)
                buffer = check_line(data, buffer, data->token[i + 1]. litteral[0], cmd);
            if(buffer == NULL && g_sig_recieved == 1)
                interrupt_heredoc(data, new, cmd);
            close(data->token[cmd].fdin);
        }
        i++;
    }
    init_signal_handler(3);
    return(0);
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
    set_heredoc(data);
}

