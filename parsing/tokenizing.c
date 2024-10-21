/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:01:11 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/21 18:24:54 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenise(t_data *data, int *i)
{
	if (init_token(&data->token[*i]) != 0)
		return (3);
	data->token[*i].tab[0] = ft_substr(data->source, data->start, (data->cur
				- data->start));
	if (data->token[*i].tab[0] == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	data->nb_token += 1;
	data->token[*i].position = data->nb_token;
	(*i)++;
	return (1);
}

int	split_token(t_data *data, char *s, int *i, int tok)
{
	if (s[data->cur] != ' ' && s[data->cur] != '\0')
	{
		while (s[data->cur] != '\"' && s[data->cur] != '\''
			&& s[data->cur] != ' ' && s[data->cur] != '\0')
			data->cur++;
		if (s[data->cur] == '\'')
		{
			data->cur = check_quote(s, data->cur, '\'');
			if (data->cur == -1)
				return (put_error(ERR_SYNTAX, "\'"), data->status = 1, -1);
		}
		if (s[data->cur] == '\"')
		{
			data->cur = check_quote(s, data->cur, '\"');
			if (data->cur == -1)
				return (put_error(ERR_SYNTAX, "\""), data->status = 1, -1);
		}
		while (s[data->cur] != '\"' && s[data->cur] != '\''
			&& s[data->cur] != ' ' && s[data->cur] != '\0')
			data->cur++;
		if (s[data->cur] == '\0' || s[data->cur] == ' ')
			tok = tokenise(data, i);
	}
	return (tok);
}

void	search_start(char *s, int *cur, int *start)
{
	while (s[*cur] == ' ' && s[*cur] != '\0')
	{
		(*cur)++;
		*start = *cur;
	}
}

int	search_token(char *s, t_data *data)
{
	int	i;
	int	tok;

	tok = 0;
	i = 0;
	data->start = data->cur;
	data->token = malloc(sizeof(t_token) * (data->lenght_token + 1));
	if (data->token == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	while (s[data->cur] != '\0')
	{
		search_start(s, &data->cur, &data->start);
		if (tok == 1)
		{
			data->start = data->cur;
			tok = 0;
		}
		tok = split_token(data, s, &i, tok);
		if (tok == -1)
			break ;
		if (tok == 3)
			return (tok);
	}
	return (0);
}
