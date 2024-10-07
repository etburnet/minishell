/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:01:11 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/07 17:31:32 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenise(t_data *data, int i)
{
	init_token(&data->token[i]);
	data->token[i].litteral[0] = ft_substr(data->source, data->start, (data->cur - data->start));
	data->nb_token += 1;
	data->token[i].position = data->nb_token;
	i++;
	return(i);
}
int		split_token(t_data *data, char *s, int i)
{
	 while(s[data->cur] == ' ')
		data->cur++;
	data->start = data->cur;
	if (s[data->cur] != ' ' && s[data->cur] != '\0')
	{
		while (s[data->cur] != '\"' && s[data->cur] != '\'' && s[data->cur] != ' ' && s[data->cur] != '\0')
			data->cur++;;
		data->cur = check_quote(s, data->cur, '\'');
		if(data->cur == -1)
			return(put_error("error invalid command", NULL), -1);
			return(put_error("error invalid command", NULL), -1);
		data->cur = check_quote(s, data->cur, '\"');
		if(data->cur == -1)
			return(put_error("error invalid command", NULL), -1);
			return(put_error("error invalid command", NULL), -1);
		while (s[data->cur] != '\"' && s[data->cur] != '\'' && s[data->cur] != ' ' && s[data->cur] != '\0')
			data->cur++;;
		if(s[data->cur] == ' ' || s[data->cur] == '\0')
			i = tokenise(data, i);
	}
	return(i);
}

int		search_token(char *s, t_data *data)
{
	int i;
	
	i = 0;
	data->token = malloc(sizeof(t_token) * data->lenght_token);
	while (s[data->cur] != '\0')
    {
       i = split_token(data, s, i);
    }
	identify_token(data);
	identify_command(data);
	execution(data);
	free_data_token(data);
	return(0);
}
// 	return(0);
// }

// 	i = 0;
// 	while(i < data->lenght_token)
// 	{
// 		printf("token %d pos %d = %s\n", i, data->token[i].position, data->token[i].litteral);
// 		i++;
// 	}
// 	return(0);
// }