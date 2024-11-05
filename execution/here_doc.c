/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:13:09 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/05 16:24:43 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_here_doc(t_data *data, int new, int cmd, int i)
{
	int		del;
	char	*buffer;

	del = 0;
	data->del = data->token[i + 1].tab[0];
	data->token[cmd].fdin = open_file(data, data->token[i], 3, cmd);
	if (data->token[cmd].fdin == -1)
		return (-1);
	buffer = readline(">");
	if (buffer == NULL && g_sig_recieved == 0)
		return (g_sig_recieved = 1, close(new), ft_free(buffer),
			close(data->token[cmd].fdin), unlink(data->token[cmd].here_doc), 3);
	while (buffer != NULL)
	{
		buffer = check_line(data, data->token[cmd].fdin, buffer, &del);
		if (buffer == NULL && del == 0 && g_sig_recieved == 0)
			return (g_sig_recieved = 1, close(new), ft_free(buffer),
				close(data->token[cmd].fdin), unlink(data->token[cmd].here_doc),
				3);
	}
	if (buffer == NULL && g_sig_recieved == 1)
		return (close(data->token[cmd].fdin), ft_free(buffer),
			interrupt_heredoc(data, new, cmd));
	close(data->token[cmd].fdin);
	return (ft_free(buffer), 0);
}

void	cmd_is_del(t_data *data, int cmd)
{
	if (data->token[cmd].type == delimiter)
	{
		if (data->token[cmd].fdin)
			close(data->token[cmd].fdin);
		unlink(data->token[cmd].here_doc);
	}
}

int	parsing_here_doc(t_data *data, int i, int *new)
{
	if ((i + 1) >= data->lenght_token)
		return (put_error(ERR_SYNTAX, &data->token[i].tab[0][0]),
			data->status = 2, 1);
	if (check_operator(data->token[i + 1].tab[0][0]) == 1)
		return (put_error(ERR_SYNTAX, &data->token[i + 1].tab[0][0]),
			data->status = 2, 1);
	data->token[i + 1].type = delimiter;
	*new = dup(0);
	if (*new == -1)
		return (perror("dup"), -1);
	return (0);
}

int	set_heredoc(t_data *data, int i)
{
	int	cmd;
	int	new;
	int	ret;

	while (i < data->lenght_token)
	{
		if (data->token[i].type == here_doc)
		{
			ret = parsing_here_doc(data, i, &new);
			if (ret != 0)
				return (ret);
			cmd = search_cmd(data, i, i);
			signal(SIGINT, ft_here_doc_signal);
			signal(SIGQUIT, SIG_IGN);
			ret = process_here_doc(data, new, cmd, i);
			if (ret != 0)
				return (ret);
			close(new);
			signal(SIGINT, ft_signal);
			cmd_is_del(data, cmd);
		}
		i++;
	}
	return (0);
}
