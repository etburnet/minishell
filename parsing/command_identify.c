/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:43:04 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/18 13:40:05 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_heredoc(t_data *data)
{
	char	*buffer;
	int		cmd;
	int		i;
	int		new;
	int del;
	
	del = 0;
	i = 0;
	init_signal_handler(2);
	while (i < data->lenght_token)
	{
		if (data->token[i].type == here_doc)
		{
			if ((new = dup(0)) == -1)
				return (perror("OUT dup"), -1);
			cmd = search_cmd(data, i);
			data->token[cmd].fdin = open_file(data, data->token[i], 3);
			if (data->token[cmd].fdin == -1)
				return (-1);
			//printf("fdin %d\n", data->token[cmd].fdin );
			buffer = readline(">");
			// if (buffer == NULL)
			// 	return (put_error(ERR_MALLOC, NULL), 3);
			while (buffer != NULL)
			{
				buffer = check_line(data->token[cmd].fdin, buffer, data->token[i + 1].tab[0], &del);
				if (buffer == NULL && del == 0)
					return (put_error(ERR_MALLOC, NULL), 3);
			}
			if (buffer == NULL && g_sig_recieved == 1)
				interrupt_heredoc(data, new, cmd);
			close(data->token[cmd].fdin);
			data->token[cmd].fdin = open_file(data, data->token[i], 4);
			if (data->token[cmd].fdin == -1)
				return (-1);
			close(new);
		}
		i++;
	}
	init_signal_handler(3);
	return (0);
}

int	check_command(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == word || data->token[i].type == string)
		{
			data->token[i].type = command;
			data->token[i].full_path = ft_find_cmd(data,
					data->token[i].tab);
			if (check_arg(data, i, command) == 3)
				return (3);
		}
		i++;
	}
	return (0);
}

void	check_outfile(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		if ((data->token[i].type == greater
			|| data->token[i].type == append))
		{
			if ((i + 1) < data->lenght_token && (data->token[i + 1].type == word
					|| data->token[i + 1].type == string || data->token[i + 1].type == append_out))
				data->token[i + 1].type = outfile;
		}
		i++;
	}
}

void	check_infile(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == less)
		{
			if (i + 1 < data->lenght_token && (data->token[i + 1].type == word
					|| data->token[i + 1].type == string))
				data->token[i + 1].type = infile;
		}
		i++;
	}
}

int	is_built_in(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		while( i < data->lenght_token && data->token[i].type != string && data->token[i].type != word)
			i++;
		if(i == data->lenght_token)
			break;
		if (ft_strncmp(data->token[i].tab[0], "echo", 5) == 0)
			data->token[i].type = built_in;
		else if (ft_strncmp(data->token[i].tab[0], "cd", 3) == 0)
			data->token[i].type = built_in;
		else if (ft_strncmp(data->token[i].tab[0], "pwd", 4) == 0)
			data->token[i].type = built_in;
		else if (ft_strncmp(data->token[i].tab[0], "export", 7) == 0)
			data->token[i].type = built_in;
		else if (ft_strncmp(data->token[i].tab[0], "unset", 6) == 0)
			data->token[i].type = built_in;
		else if (ft_strncmp(data->token[i].tab[0], "env", 4) == 0)
			data->token[i].type = built_in;
		else if (ft_strncmp(data->token[i].tab[0], "exit", 5) == 0)
			data->token[i].type = built_in;
		if (data->token[i].type == built_in)
			if (check_arg(data, i, built_in) == 3)
				return (3);
		i++;
	}
	return (0);
}

int	is_special_char(char *s)
{
	if (ft_strncmp(s, "#", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "!", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "$#", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$*", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$@", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$_", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$-", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$!", 3) == 0)
		return (1);
	else if (ft_strncmp(s, ";", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "|", 2) == 0)
		return (1);
	return (0);
}

int	is_special_char_bis(char *s)
{
	if (ft_strncmp(s, ";;", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "`", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ":", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "&", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "&&", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "()", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "(", 1) == 0)
		return (1);
	else if (ft_strncmp(s, ")", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "||", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "%%", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<>", 3) == 0)
		return (1);
	return (0);
}

int	first_is_chevron(t_data *data, char *s)
{
	if (ft_strncmp(s, "<", 2) == 0 && data->token[1].type != infile)
		return (1);
	else if (ft_strncmp(s, ">", 2) == 0 && data->token[1].type != outfile)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0 && data->token[1].type != here_doc)
		return (1);
	else if (ft_strncmp(s, ">>", 3) == 0 && data->token[1].type != outfile)
		return (1);
	return (0);
}
int		is_chevrons(char *s)
{
	if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	return(0);
}

int	check_first_token(t_data *data)
{
	DIR			*stream_dir;
	
	if (data->nb_token == 0)
		return (0);
	stream_dir = opendir(data->token[0].tab[0]);
	if (stream_dir != NULL)
		return (closedir(stream_dir), put_error("is a directory: ", data->token[0].tab[0]), 1);
	if (is_special_char(data->token[0].tab[0]) == 1)
		return (put_error(ERR_SYNTAX, data->token[0].tab[0]), 1);
	if (is_special_char_bis(data->token[0].tab[0]) == 1)
		return (put_error(ERR_SYNTAX, data->token[0].tab[0]), 1);
	if(data->nb_token >= 2)
	{
		if (first_is_chevron(data, data->token[0].tab[0]) == 1)
			return (put_error(ERR_SYNTAX, data->token[0].tab[0]), 1);
	}
	else if(data->nb_token == 1)	
	{
		if(is_chevrons(data->token[0].tab[0]) == 1)
			return(put_error(ERR_SYNTAX, data->token[0].tab[0]), 1);
	}
	return (0);
}

int	identify_command(t_data *data)
{
	int	ret;

	if (is_built_in(data) == 3)
		return (3);
	check_infile(data);
	check_outfile(data);
	if (check_command(data) == 3)
		return (3);
	if (check_first_token(data) == 1)
		return (1);
	ret = set_heredoc(data);
	if (ret != 0)
		return (ret);
	return (0);
}
