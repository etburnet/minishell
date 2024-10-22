/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:13:09 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/22 12:41:29 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_init_here(char *str, char **res, char **var, char **tok_dup)
{
	*res = malloc(sizeof(char) * BUFSIZ);
	if (!res)
		return (3);
	memset(*res, '\0', BUFSIZ);
	*var = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!var)
		return (ft_free(*res), 3);
	*tok_dup = ft_strdup(str);
	if (tok_dup == NULL)
		return (ft_free(*res), ft_free(*var), 3);
	return (0);
}
int	expand_here_doc(t_data *data, char **str)
{
	t_expand	exp;

	exp.i = 0;
	exp.j = 0;
	exp.k = 0;
	exp.dq = 0;
	if (expand_init_here(*str, &exp.res, &exp.var, &exp.tok_dup) == 3)
		return (put_error(ERR_MALLOC, NULL), 3);
	if (expand_loop(data, &exp) == 3)
		return (ft_free(exp.var), ft_free(exp.res), ft_free(exp.tok_dup), 3);
	exp.res[exp.i] = '\0';
	ft_free(*str);
	*str = exp.res;
	return (ft_free(exp.var), ft_free(exp.tok_dup), 0);
}

int	process_here_doc(t_data *data, int new, int cmd, int i)
{
	int		del;
	char	*buffer;

	del = 0;
	data->del = data->token[i + 1].tab[0];
	data->token[cmd].fdin = open_file(data, data->token[i], 3);
	if (data->token[cmd].fdin == -1)
		return (-1);
	buffer = readline(">");
	if (buffer == NULL && g_sig_recieved == 0)
		return (ft_free(buffer), close(data->token[cmd].fdin), put_error(ERR_MALLOC, NULL), 3);
	while (buffer != NULL)
	{
		buffer = check_line(data, data->token[cmd].fdin, buffer, &del);
		if (buffer == NULL && del == 0 && g_sig_recieved == 0)
			return (ft_free(buffer), close(data->token[cmd].fdin), put_error(ERR_MALLOC, NULL), 3);
	}
	if (buffer == NULL && g_sig_recieved == 1)
		return (ft_free(buffer), interrupt_heredoc(data, new, cmd), 1);
	close(data->token[cmd].fdin);
	return (ft_free(buffer), 0);
}

int	set_heredoc(t_data *data, int i)
{
	int	cmd;
	int	new;
	int	ret;

	init_signal_handler(data, 2);
	while (i < data->lenght_token)
	{
		if (data->token[i].type == here_doc)
		{
			new = dup(0);
			if (new == -1)
				return (perror("OUT dup"), -1);
			cmd = search_cmd(data, i);
			ret = process_here_doc(data, new, cmd, i);
			if (ret != 0)
				return (ret);
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
