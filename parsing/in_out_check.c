/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:15:08 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/20 11:25:36 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_outfile(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == greater)
		{
			if ((i + 1) < data->lenght_token && check_operator(data->token[i
						+ 1].tab[0][0]) == 1)
				return (put_error(ERR_SYNTAX, &data->token[i + 1].tab[0][0]),
					data->status = 1, 1);
			if ((i + 1) < data->lenght_token && (data->token[i + 1].type == word
					|| data->token[i + 1].type == string))
			{
				data->token[i + 1].type = outfile;
				fd = open(data->token[i + 1].tab[0],
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
					return (perror(data->token[i + 1].tab[0]), data->status = 1,
						-1);
				else
					close(fd);
			}
		}
		else if (data->token[i].type == append)
		{
			if ((i + 1) < data->lenght_token && check_operator(data->token[i
						+ 1].tab[0][0]) == 1)
				return (put_error(ERR_SYNTAX, &data->token[i + 1].tab[0][0]),
					data->status = 1, 1);
			if ((i + 1) < data->lenght_token && (data->token[i + 1].type == word
					|| data->token[i + 1].type == string))
			{
				data->token[i + 1].type = append_out;
				fd = open(data->token[i + 1].tab[0],
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0)
					return (perror(data->token[i + 1].tab[0]), data->status = 1,
						-1);
				else
					close(fd);
			}
		}
		i++;
	}
	return (0);
}

int	check_infile(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == less)
		{
			if ((i + 1) < data->lenght_token && check_operator(data->token[i
						+ 1].tab[0][0]) == 1)
				return (put_error(ERR_SYNTAX, &data->token[i + 1].tab[0][0]),
					1);
			if (i + 1 < data->lenght_token && (data->token[i + 1].type == word
					|| data->token[i + 1].type == string))
				data->token[i + 1].type = infile;
		}
		i++;
	}
	return (0);
}
