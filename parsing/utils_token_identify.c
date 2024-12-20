/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_identify.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:41:19 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/11/05 13:48:37 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_string_to_cpy(char *s, char *tmp, int *i, int *j)
{
	tmp[*j] = s[*i];
	(*j)++;
	(*i)++;
}

char	*check_to_remove_dquote(char *s, char *tmp, int *j, int *i)
{
	int	quote;

	quote = 0;
	if (s[*i] == '\"' && s[*i] != '\0')
	{
		(*i)++;
		quote = 1;
		while (s[*i] != '\"' && s[*i] != '\0')
			put_string_to_cpy(s, tmp, i, j);
		if (s[*i] == '\"' && s[*i] != '\0')
		{
			quote = 0;
			(*i)++;
		}
		if (s[*i] == '\0' && quote == 1)
			return (NULL);
	}
	return (tmp);
}

char	*check_to_remove_quote(char *s, char *tmp, int *j, int *i)
{
	int	quote;

	quote = 0;
	if (s[*i] == '\'' && s[*i] != '\0')
	{
		(*i)++;
		quote = 1;
		while (s[*i] != '\'' && s[*i] != '\0')
			put_string_to_cpy(s, tmp, i, j);
		if (s[*i] == '\'' && s[*i] != '\0')
		{
			quote = 0;
			(*i)++;
		}
		if (s[*i] == '\0' && quote == 1)
			return (NULL);
	}
	return (tmp);
}

char	*remove_quote(char *s, int i, int j)
{
	char	*tmp;

	tmp = malloc((ft_strlen(s) + 1));
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, '\0', ft_strlen(s) + 1);
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			put_string_to_cpy(s, tmp, &i, &j);
		if (s[i] != ' ' && s[i] != '\0')
		{
			while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
				put_string_to_cpy(s, tmp, &i, &j);
			if (check_to_remove_quote(s, tmp, &j, &i) == NULL
				|| check_to_remove_dquote(s, tmp, &j, &i) == NULL)
				return (ft_free(tmp), NULL);
			while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
				put_string_to_cpy(s, tmp, &i, &j);
		}
	}
	ft_free(s);
	return (tmp);
}

int	is_metacharcter(char *s, int i)
{
	if (s[i] == '\\' || s[i] == '\n' || s[i] == '\t')
		return (1);
	return (0);
}
