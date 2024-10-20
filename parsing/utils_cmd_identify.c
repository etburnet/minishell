/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_identify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:18:49 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/21 18:34:05 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_cmd(t_data *data, int i)
{
	int	index;

	index = i;
	i--;
	while (i >= 0)
	{
		if (data->token[i].type == command || data->token[i].type == built_in)
			return (i);
		i--;
	}
	if (i == -1)
	{
		index = i;
		while (i < data->lenght_token && data->token[i].type != pipes)
		{
			if (data->token[i].type == command
				|| data->token[i].type == built_in)
				return (i);
			i++;
		}
	}
	return (i);
}

char	*check_line(int fdin, char *buffer, char *delimiter, int *del)
{
	if (ft_strncmp(buffer, delimiter, (strlen(delimiter) + 1)) == 0)
	{
		*del = 1;
		return (NULL);
	}
	write(fdin, buffer, ft_strlen(buffer) + 1);
	write(fdin, "\n", 2);
	buffer = readline(">");
	return (buffer);
}

int	interrupt_heredoc(t_data *data, int new, int cmd)
{
	if (dup2(new, STDIN_FILENO) == -1)
		return (perror("dup2"), -1);
	close(data->token[cmd].fdin);
	unlink("temp_file_here_doc.txt");
	return (0);
}

int	set_arg(t_data *data, int i, int cmd, int j)
{
	data->token[cmd].nb_arg += 1;
	if (data->token[cmd].nb_arg + 1 > data->token[cmd].size)
	{
		data->token[cmd].tab = my_realloc(data->token[cmd],
				data->token[cmd].size);
		if (data->token[cmd].tab == NULL)
			return (put_error(ERR_MALLOC, NULL), 3);
		data->token[cmd].size += 1;
	}
	data->token[cmd].tab[j] = ft_strdup(data->token[i].tab[0]);
	if (data->token[cmd].tab[j] == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	return (0);
}

int	check_arg(t_data *data, int i, t_type type)
{
	int	j;
	int	cmd;

	j = 1;
	i++;
	while (i < data->lenght_token)
	{
		if ((data->token[i - 1].type == type || data->token[i - 1].type == arg)
			&& (data->token[i].type == word || data->token[i].type == string))
		{
			if (data->token[i - 1].type == type)
				cmd = i - 1;
			data->token[i].type = arg;
			if (set_arg(data, i, cmd, j) != 0)
				return (3);
			j++;
		}
		i++;
	}
	return (0);
}
