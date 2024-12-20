/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:34:13 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/11/05 13:49:37 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(const char *s, int i, char c)
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
			i++;
			return (i);
		}
		if (s[i] == '\0' && quote == 1)
			return (-1);
	}
	return (i);
}

size_t	ft_countword(const char *s, int i)
{
	size_t	count;

	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != ' ' && s[i] != '\0')
		{
			while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
				i++;
			i = check_quote(s, i, '\"');
			if (i == -1)
				return (-1);
			i = check_quote(s, i, '\'');
			if (i == -1)
				return (-1);
			while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
				i++;
			if (s[i] == ' ' || s[i] == '\0')
				count++;
		}
	}
	return (count);
}

int	ft_strchr_edit(const char *s, char c)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			res += 1;
		i++;
	}
	return (res);
}

int	ft_isdigit_edit(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-' || c[i] == '+')
		return (1);
	while (c[i] != '\0')
	{
		if (c[i] >= '0' && c[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

char	*set_temp(t_data *data)
{
	char	*temp;

	temp = ft_strdup(data->arg);
	if (temp == NULL)
		return (NULL);
	return (temp);
}
