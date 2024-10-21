/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:21:17 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/20 11:26:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	if (c == '|' || c == '&')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}

void	add_space(char *temp, int *j)
{
	temp[*j] = ' ';
	(*j)++;
}

int	count_space(t_data *data, char *s, int i, int j)
{
	while (s[i] != '\0')
	{
		i = check_quote(s, i, '\'');
		if (i == -1)
			return (put_error(ERR_SYNTAX, "\'"), data->status = 1, 0);
		i = check_quote(s, i, '\"');
		if (i == -1)
			return (put_error(ERR_SYNTAX, "\""), data->status = 1, 0);
		if (check_operator(s[i]) == 1)
		{
			if (s[i] == s[i + 1])
			{
				if (i > 0 && s[i - 1] != ' ')
					j++;
				i++;
				if (s[i + 1] != '\0')
				{
					if (s[i + 1] != ' ')
						j++;
					i++;
				}
			}
			else
			{
				if (i > 0 && s[i - 1] != ' ')
					j++;
				if (s[i] != '\0' && s[i + 1] != ' ')
					j++;
				i++;
			}
		}
		else if (s[i] != '\0')
			i++;
	}
	return (j + i);
}
