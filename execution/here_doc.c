/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:13:09 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/20 14:44:10 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_heredoc(t_data *data)
{
	char	*buffer;
	int		cmd;
	int		i;
	int		new;
	int		del;

	del = 0;
	i = 0;
	init_signal_handler(data, 2);
	while (i < data->lenght_token)
	{
		if (data->token[i].type == here_doc)
		{
			new = dup(0);
			if (new == -1)
				return (perror("OUT dup"), -1);
			cmd = search_cmd(data, i);
			data->token[cmd].fdin = open_file(data, data->token[i], 3);
			if (data->token[cmd].fdin == -1)
				return (-1);
			buffer = readline(">");
			if (buffer == NULL && g_sig_recieved == 0)
				return (put_error(ERR_MALLOC, NULL), 3);
			while (buffer != NULL)
			{
				buffer = check_line(data->token[cmd].fdin, buffer, data->token[i
						+ 1].tab[0], &del);
				if (buffer == NULL && del == 0 && g_sig_recieved == 0)
					return (put_error(ERR_MALLOC, NULL), 3);
			}
			if (buffer == NULL && g_sig_recieved == 1)
				return (interrupt_heredoc(data, new, cmd), 1);
			close(data->token[cmd].fdin);
			data->token[cmd].fdin = open_file(data, data->token[i], 4);
			if (data->token[cmd].fdin == -1)
				return (-1);
			close(new);
		}
		i++;
	}
	init_signal_handler(data, 3);
	return (0);
}
