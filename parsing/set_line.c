/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:30:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/11/05 13:49:57 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_double_op(char *s, char *temp, int *i, int *j)
{
	if (*i > 0 && s[*i - 1] != ' ' && temp[*j - 1] != ' ')
		add_space(temp, j);
	put_string_to_cpy(s, temp, i, j);
	if (s[*i + 1] != ' ')
	{
		put_string_to_cpy(s, temp, i, j);
		add_space(temp, j);
	}
	else
		put_string_to_cpy(s, temp, i, j);
}

void	is_operator(char *s, char *temp, int *i, int *j)
{
	if (s[*i] == s[*i + 1])
		process_double_op(s, temp, i, j);
	else
	{
		if (s[*i + 1] != ' ' && (*i > 0 && s[*i - 1] != ' ') && temp[*j
				- 1] != ' ')
		{
			add_space(temp, j);
			put_string_to_cpy(s, temp, i, j);
			add_space(temp, j);
		}
		else if (s[*i + 1] != ' ')
		{
			put_string_to_cpy(s, temp, i, j);
			add_space(temp, j);
		}
		else if (*i > 0 && s[*i - 1] != ' ')
		{
			add_space(temp, j);
			put_string_to_cpy(s, temp, i, j);
		}
		else
			put_string_to_cpy(s, temp, i, j);
	}
}

char	*check_to_remove_quote_edit(char *s, char *tmp, int *j, int *i)
{
	int	quote;

	quote = 0;
	if (s[*i] == '\'' && s[*i] != '\0')
	{
		put_string_to_cpy(s, tmp, i, j);
		quote = 1;
		while (s[*i] != '\'' && s[*i] != '\0')
			put_string_to_cpy(s, tmp, i, j);
		if (s[*i] == '\'' && s[*i] != '\0')
		{
			quote = 0;
			put_string_to_cpy(s, tmp, i, j);
		}
		if (s[*i] == '\0' && quote == 1)
			return (NULL);
	}
	return (tmp);
}

char	*check_to_remove_dquote_edit(char *s, char *tmp, int *j, int *i)
{
	int	quote;

	quote = 0;
	if (s[*i] == '\"' && s[*i] != '\0')
	{
		put_string_to_cpy(s, tmp, i, j);
		quote = 1;
		while (s[*i] != '\"' && s[*i] != '\0')
			put_string_to_cpy(s, tmp, i, j);
		if (s[*i] == '\"' && s[*i] != '\0')
		{
			quote = 0;
			put_string_to_cpy(s, tmp, i, j);
		}
		if (s[*i] == '\0' && quote == 1)
			return (NULL);
	}
	return (tmp);
}

char	*set_string(t_data *data, char *s, int len, int len_arg)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (len == len_arg)
		return (set_temp(data));
	temp = malloc(sizeof(char) * (len + 2));
	if (temp == NULL)
		return (NULL);
	ft_memset(temp, '\0', len + 1);
	while (i < len_arg)
	{
		if ((check_operator(s[i]) != 1) && s[i] != '\'' && s[i] != '\"')
			put_string_to_cpy(s, temp, &i, &j);
		else if (s[i] == '\"')
			check_to_remove_dquote_edit(s, temp, &j, &i);
		else if (s[i] == '\'')
			check_to_remove_quote_edit(s, temp, &j, &i);
		else if (check_operator(s[i]) == 1)
			is_operator(s, temp, &i, &j);
	}
	return (temp);
}
