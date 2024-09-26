/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:54 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/26 14:04:26 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_quote(const char *s, int i, char c)
{
    int quote;
    
    quote = 0;
    if(s[i] == c && s[i] != '\0')
    {
        i++;
        quote = 1;
        while(s[i] != c && s[i] != '\0')
            i++;
        if(s[i] == c && s[i] != '\0')
        { 
            quote = 0;
            i++;
        }
        if(s[i] == '\0' && quote == 1)
            return(0);
    }
    return(i);
}

static size_t    ft_countword(const char *s, int i)
{
    size_t    count;
    
    count = 0;
    while (s[i] != '\0')
    {
        while(s[i] == ' ')
            i++;
        if (s[i] != ' ' && s[i] != '\0')
        {
            while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
                i++;
            i = check_quote(s, i, '\"');
            if(i == 0)
                return(0);
            i = check_quote(s, i, '\'');
            if(i == 0)
                return(0);
            while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
                i++;
            if(s[i] == ' ' || s[i] == '\0')
                count++;
        }
    }
    return (count);
}

int	ft_strchr(const char *s, char c)
{
	int				i;
	int res;
	
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

char	*ft_strdup(const char *s)
{
	size_t	len;
	int		i;
	char	*news;

	len = 0;
	i = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	news = malloc(len + 1);
	if (news == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		news[i] = s[i];
		i++;
	}
	news[i] = '\0';
	return (news);
}
void	init_tokenizer_state(t_tokenizer *tok, char *s)
{
	tok->nb_token = 0;
	tok->lenght_token = ft_countword(s, 0);
	tok->cur = 0;
	tok->source_lenght = (int)ft_strlen(s);
	tok->start = 0;
	tok->source = ft_strdup(s);
}
void	init_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	token->lexeme = undefine;
	token->value = 0;
	token->position = 0;
}
int	tokenise(t_tokenizer *tok, int i)
{
	init_token(&tok->token[i]);
	tok->token[i].litteral = ft_substr(tok->source, tok->start, (tok->cur - tok->start));
	tok->nb_token += 1;
	tok->token[i].position = tok->nb_token;
	i++;
	return(i);
}

void		check_arg(char *s, t_tokenizer *tok)
{
	int i;
	
	i = 0;
	tok->token = malloc(sizeof(t_token) * tok->lenght_token);
	while (s[tok->cur] != '\0')
    {
        while(s[tok->cur] == ' ')
            tok->cur++;
		tok->start = tok->cur;
        if (s[tok->cur] != ' ' && s[tok->cur] != '\0')
        {
            while (s[tok->cur] != '\"' && s[tok->cur] != '\'' && s[tok->cur] != ' ' && s[tok->cur] != '\0')
                tok->cur++;;
           	tok->cur = check_quote(s, tok->cur, '\'');
			if(tok->cur == 0)
				ft_error();
            tok->cur = check_quote(s, tok->cur, '\"');
			if(tok->cur == 0)
				ft_error();
            while (s[tok->cur] != '\"' && s[tok->cur] != '\'' && s[tok->cur] != ' ' && s[tok->cur] != '\0')
                tok->cur++;;
            if(s[tok->cur] == ' ' || s[tok->cur] == '\0')
				i = tokenise(tok, i);
		}
    }
}

// i = 0;
// 	while(i < tok->lenght_token)
// 	{
// 		printf("token %d pos %d = %s\n", i, tok->token[i].position, tok->token[i].litteral);
// 		i++;
// 	}