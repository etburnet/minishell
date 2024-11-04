/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:15:08 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/04 16:27:21 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_greater(t_data *data, int i)
{
	if ((i + 1) < data->lenght_token && check_operator(data->token[i
			+ 1].tab[0][0]) == 1)
		return (put_error(ERR_SYNTAX, &data->token[i + 1].tab[0][0]),
			data->status = 2, 1);
	if ((i + 1) >= data->lenght_token)
		return (put_error(ERR_SYNTAX, &data->token[i].tab[0][0]),
			data->status = 2, 1);
	if ((i + 1) < data->lenght_token && (data->token[i + 1].type == word
			|| data->token[i + 1].type == string))
	{
		data->token[i + 1].type = outfile;
	}
	return (0);
}

int	is_append(t_data *data, int i)
{
	if ((i + 1) < data->lenght_token && check_operator(data->token[i
			+ 1].tab[0][0]) == 1)
		return (put_error(ERR_SYNTAX, &data->token[i + 1].tab[0][0]),
			data->status = 2, 1);
	if ((i + 1) >= data->lenght_token)
		return (put_error(ERR_SYNTAX, &data->token[i].tab[0][0]),
			data->status = 2, 1);
	if ((i + 1) < data->lenght_token && (data->token[i + 1].type == word
			|| data->token[i + 1].type == string))
	{
		data->token[i + 1].type = append_out;
	}
	return (0);
}

int	check_outfile(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == greater)
		{
			ret = is_greater(data, i);
			if (ret != 0)
				return (ret);
		}
		else if (data->token[i].type == append)
		{
			ret = is_append(data, i);
			if (ret != 0)
				return (ret);
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
			if ((i + 1) >= data->lenght_token)
				return (put_error(ERR_SYNTAX, &data->token[i].tab[0][0]),
					data->status = 2, 1);
			if (i + 1 < data->lenght_token && (data->token[i + 1].type == word
					|| data->token[i + 1].type == string))
				data->token[i + 1].type = infile;
		}
		i++;
	}
	return (0);
}
