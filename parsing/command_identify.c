/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:43:04 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/23 13:08:35 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		if (data->token[i].type == word || data->token[i].type == string)
		{
			if (data->token[i].tab[0][0] == '\0')
				data->token[i].type = word;
			else
			{
				data->token[i].type = command;
				data->token[i].full_path = ft_find_cmd(data,
						data->token[i].tab);
				if (check_arg(data, i, command) == 3)
					return (3);
			}
		}
		i++;
	}
	return (0);
}

void	comp_built_in(t_data *data, int i)
{
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
}

int	is_built_in(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lenght_token)
	{
		while (i < data->lenght_token && data->token[i].type != string
			&& data->token[i].type != word)
			i++;
		if (i == data->lenght_token)
			break ;
		comp_built_in(data, i);
		if (data->token[i].type == built_in)
			if (check_arg(data, i, built_in) == 3)
				return (3);
		i++;
	}
	return (0);
}

int	check_first_token(t_data *data)
{
	if (data->nb_token == 0)
		return (0);
	if (is_special_char(data->token[0].tab[0]) == 1)
		return (1);
	if (is_special_char_bis(data->token[0].tab[0]) == 1)
		return (1);
	if (data->nb_token >= 2)
	{
		if (first_is_chevron(data, data->token[0].tab[0]) == 1)
			return (1);
	}
	else if (data->nb_token == 1)
		if (is_chevrons(data->token[0].tab[0]) == 1)
			return (1);
	return (0);
}

int	identify_command(t_data *data)
{
	int	ret;

	if (check_infile(data) != 0)
		return (data->status = 1, 1);
	if (check_outfile(data) != 0)
		return (1);
	if (is_built_in(data) == 3)
		return (3);
	if (check_command(data) == 3)
		return (3);
	if (check_first_token(data) == 1)
		return (put_error(ERR_SYNTAX, data->token[0].tab[0]), data->status = 1,
			1);
	ret = set_heredoc(data, 0);
	if (ret != 0)
		return (ret);
	// int i = 0;
	// while(i < data->lenght_token)
	// {
	// 	printf("tok %d = %s, type %d\n", i, data->token[i].tab[0], data->token[i].type);
	// 	i++;
	// }
	return (0);
}
