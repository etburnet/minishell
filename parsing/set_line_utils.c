/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:21:17 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/21 18:33:23 by opdi-bia         ###   ########.fr       */
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

void	process_operator(char *s, int *i, int *j)
{
	if (s[*i] == s[*i + 1])
	{
		if (*i > 0 && s[*i - 1] != ' ')
			(*j)++;
		(*i)++;
		if (s[*i + 1] != '\0')
		{
			if (s[*i + 1] != ' ')
				(*j)++;
			(*i)++;
		}
	}
	else
	{
		if (*i > 0 && s[*i - 1] != ' ')
			(*j)++;
		if (s[*i] != '\0' && s[*i + 1] != ' ')
			(*j)++;
		(*i)++;
	}
}

int	there_is_quote(const char *s, int i, char c)
{
	int	quote;

	quote = 0;
	if (s[i] == c)
	{
		i++;
		quote = 1;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == c)
		{
			quote = 0;
			return (i);
		}
		if (s[i] == '\0' && quote == 1)
			return (-1);
	}
	return (i);
}

int	count_space(t_data *data, char *s, int i, int j)
{
	while (s[i] != '\0')
	{
		i = there_is_quote(s, i, '\'');
		if (i == -1)
			return (put_error(ERR_SYNTAX, "\'"), data->status = 1, 0);
		i = there_is_quote(s, i, '\"');
		if (i == -1)
			return (put_error(ERR_SYNTAX, "\""), data->status = 1, 0);
		if (check_operator(s[i]) == 1)
			process_operator(s, &i, &j);
		else if (s[i] != '\0')
			i++;
	}
	return (j + i);
}
