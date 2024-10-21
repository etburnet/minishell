/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/21 17:40:12 by opdi-bia         ###   ########.fr       */
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
			return(i);
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
