/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_identify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:18:49 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/10 13:49:50 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     search_cmd(t_data *data, int i)
{
    i--;
    while(i >= 0)
    {
        if(data->token[i].type == command || data->token[i].type == built_in)
            return(i);
        i--;
    }
    return(i);
}

char    *check_line(t_data *data, char *buffer, char *delimiter, int cmd)
{
    if(strncmp(buffer, delimiter, (strlen(delimiter) + 1)) == 0)
        return(NULL);
    write(data->token[cmd].fdin, buffer, ft_strlen(buffer) + 1);
    write(data->token[cmd].fdin, "\n", 2); 
    buffer = readline(">");
    if(buffer == NULL)
        return(put_error(ERR_MALLOC, NULL), NULL);
    return(buffer);
}

int    interrupt_heredoc(t_data *data, int new, int cmd)
{
    if(dup2(new, STDIN_FILENO) == -1)
        return (perror("dup2"), -1);;
    close(data->token[cmd].fdin);
    unlink("temp_file_gere_doc.txt");
    g_sig_recieved = 0;
    return(0);
}

int    check_arg(t_data *data, int i, e_type type)
{
    int j;
    int cmd;
    
    j = 1;
    i++;
    while(i < data->lenght_token)
    {
        if((data->token[i - 1].type == type || data->token[i - 1].type == arg) && (data->token[i].type == word || data->token[i].type == string))
        {
            if(data->token[i - 1].type == type)
                cmd = i - 1;
            data->token[i].type = arg;
            data->token[cmd].nb_arg += 1;
            if(data->token[cmd].nb_arg + 1 > data->token[cmd].size)
            {
                data->token[cmd].litteral = my_realloc(data->token[cmd], data->token[cmd].size);
                if(data->token[cmd].litteral == NULL)
                    return(put_error(ERR_MALLOC, NULL), 3);
                data->token[cmd].size += 1;
            }
            data->token[cmd].litteral[j] = ft_strdup(data->token[i].litteral[0]);
            if(data->token[cmd].litteral[j] == NULL)
                return(put_error(ERR_MALLOC, NULL), 3);
            j++;
        }
        i++;
    }
    return(0);
}

