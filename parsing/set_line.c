/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:30:56 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/15 13:17:27 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (1);
	return (0);
}

int	count_space(char *s, int i, int j)
{
	while (s[i] != '\0')
	{
		i = check_quote(s, i, '\'');
		if (i == -1)
			return (-1);
		i = check_quote(s, i, '\"');
		if (i == -1)
			return (-1);
		if (check_operator(s[i]) == 1)
		{
			if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i
					+ 1] == '>'))
			{
				if (s[i - 1] != ' ')
					j++;
				i++;
				if (s[i + 1] != ' ')
					j++;
				i++;
			}
			else
			{
				if (s[i - 1] != ' ')
					j++;
				if (s[i + 1] != ' ')
					j++;
			}
		}
		i++;
	}
	return (j + i + 1);
}

void	add_space(char *temp, int *j)
{
	temp[*j] = ' ';
	(*j)++;
}

void	is_operator(char *s, char *temp, int *i, int *j)
{
	if ((s[*i] == '<' && s[*i + 1] == '<') || (s[*i] == '>' && s[*i + 1] == '>')
		|| (s[*i] == '|' && s[*i + 1] == '|'))
	{
		if (*i > 0 && s[*i - 1] != ' ')
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
	else
	{
		if (*i > 0 && s[*i - 1] != ' ')
			add_space(temp, j);
		put_string_to_cpy(s, temp, i, j);
		if (s[*i + 1] != ' ')
			add_space(temp, j);
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
char	*set_string(char *s, int len)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(*temp) * (len + 1));
	if (temp == NULL)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	ft_memset(temp, '\0', len + 1);
	while (s[i] != '\0')
	{
		if ((check_operator(s[i]) != 1) && s[i] != '\'' && s[i] != '\"')
			put_string_to_cpy(s, temp, &i, &j);
		if (s[i] == '\"')
			check_to_remove_dquote_edit(s, temp, &j, &i);
		if (s[i] == '\'')
			check_to_remove_quote_edit(s, temp, &j, &i);
		if (check_operator(s[i]) == 1)
			is_operator(s, temp, &i, &j);
	}
	return (temp);
}
