/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:01:11 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/10 12:01:49 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenise(t_data *data, int *i)
{
	if(init_token(&data->token[*i]) == -1)
		return(-1);
	data->token[*i].litteral[0] = ft_substr(data->source, data->start, (data->cur - data->start));
	if(data->token[*i].litteral[0] == NULL)
		return(put_error(ERR_MALLOC, NULL), -1);
	data->nb_token += 1;
	data->token[*i].position = data->nb_token;
	(*i)++;
	return(1);
}
int		split_token(t_data *data, char *s, int *i, int tok)
{
	if (s[data->cur] != ' ' && s[data->cur] != '\0')
	{
		while (s[data->cur] != '\"' && s[data->cur] != '\'' && s[data->cur] != ' ' && s[data->cur] != '\0')
			data->cur++;;
		data->cur = check_quote(s, data->cur, '\'');
		if(data->cur == -1)
			return(put_error(ERR_CMD, "\'"), -1);
		data->cur = check_quote(s, data->cur, '\"');
		if(data->cur == -1)
			return(put_error(ERR_CMD, "\""), -1);
		while (s[data->cur] != '\"' && s[data->cur] != '\'' && s[data->cur] != ' ' && s[data->cur] != '\0')
			data->cur++;
		if(s[data->cur] == ' ' || s[data->cur] == '\0')
			tok = tokenise(data, i);
	}
	return(tok);
}

int		search_token(char *s, t_data *data)
{
	int i;
	int tok;

	tok = 0;
	i = 0;
	data->start = data->cur;
	data->token = malloc(sizeof(t_token) * (data->lenght_token + 1));
	if(data->token == NULL)
		return(put_error(ERR_MALLOC, NULL), -1);
	while (s[data->cur] != '\0')
    {
		while(s[data->cur] == ' ')
		data->cur++;
		if(tok == 1)
		{
			data->start = data->cur;
			tok = 0;
		}
        tok = split_token(data, s, &i, tok);
		if(tok == -1)
			return(-1);
    }
	return(0);
}
