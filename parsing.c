/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:54 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/26 13:31:23 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t    ft_countword(const char *s, char c)
{
    size_t    i;
    size_t    count;
    int quote = 0;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        while(s[i] == ' ')
            i++;
        if (s[i] != c && s[i] != '\0')
        {
            while (s[i] != '\"' && s[i] != '\'' && s[i] != c && s[i] != '\0')
                i++;
            if(s[i] == '\'' && s[i] != '\0')
            {
                i++;
                quote = 1;
                while(s[i] != '\'' && s[i] != '\0')
                    i++;
                if(s[i] == '\'' && s[i] != '\0')
                { 
                    quote = 0;
                    i++;
                }
                if(s[i] == '\0' && quote == 1)
                    return(0);
            }
            if(s[i] == '\"' && s[i] != '\0')
            {
                i++;
                quote = 1;
                while(s[i] != '\"' && s[i] != '\0')
                    i++;
                if(s[i] == '\"' && s[i] != '\0')
                { 
                    quote = 0;
                    i++;
                }
                if(s[i] == '\0' && quote == 1)
                    return(0);
            }
            while (s[i] != '\"' && s[i] != '\'' && s[i] != c && s[i] != '\0')
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
// int		check_error(char *s)
// {
	
// }

// int	check_arg(char *s)
// {
// 	int nb_word;
// 	int quote;
// 	int double_quote;
// 	char	**tab;
	
// 	quote = ft_strchr(s, '\'');
// 	double_quote = ft_strchr(s, '\"');
// 	// check_error(s);
// 	if(quote % 2 != 0 || double_quote % 2 != 0)
// 		ft_error();
// 	nb_word = ft_countword(s, ' ');
// 	tab = malloc((nb_word + 1) * sizeof(char *));
// 	if (tab == NULL)
// 		return (ft_exit(s), 0);
// 	if(quote != 0)
// 		tab = ft_split(s, tab, '\'', nb_word); //stock la partie '' dans tab[index num word]
// 	if(double_quote != 0)
// 		tab = ft_split(s, tab, '\"', nb_word); //idem plus haut
// 	tab = ft_split(s, tab, ' ', nb_word); // finit de placer les mots dans tab
// 	// int i = 0;
// 	// while(i < nb_word)
// 	// {
// 	// 	printf("%s\n", tab[i]);
// 	// 	i++;
// 	// }
// 	return(0);
// }
//plusieur split a la suite a gerer, ne doit pas toucher a ce qui a deja ete split
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
	tok->lenght_token = 0;
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

int		check_arg(char *s, t_tokenizer *tok)
{
	int i;
	int quote = 0;
	i = 0;
	int word = ft_countword(s, ' ');
	tok->token = malloc(sizeof(t_token) * word);
	while (s[tok->cur] != '\0')
    {
        while(s[tok->cur] == ' ')
            tok->cur++;
		tok->start = tok->cur;
        if (s[tok->cur] != ' ' && s[tok->cur] != '\0')
        {
            while (s[tok->cur] != '\"' && s[tok->cur] != '\'' && s[tok->cur] != ' ' && s[tok->cur] != '\0')
                tok->cur++;;
            if(s[tok->cur] == '\'' && s[tok->cur] != '\0')
            {
                tok->cur++;;
                quote = 1;
                while(s[tok->cur] != '\'' && s[tok->cur] != '\0')
                    tok->cur++;;
                if(s[tok->cur] == '\'' && s[tok->cur] != '\0')
                { 
                    quote = 0;
                    tok->cur++;;
                }
                if(s[tok->cur] == '\0' && quote == 1)
                    ft_error();
            }
            if(s[tok->cur] == '\"' && s[tok->cur] != '\0')
            {
                tok->cur++;;
                quote = 1;
                while(s[tok->cur] != '\"' && s[tok->cur] != '\0')
                    tok->cur++;;
                if(s[tok->cur] == '\"' && s[tok->cur] != '\0')
                { 
                    quote = 0;
                    tok->cur++;;
                }
                if(s[tok->cur] == '\0' && quote == 1)
                    ft_error();
            }
            while (s[tok->cur] != '\"' && s[tok->cur] != '\'' && s[tok->cur] != ' ' && s[tok->cur] != '\0')
                tok->cur++;;
            if(s[tok->cur] == ' ' || s[tok->cur] == '\0')
            {
				init_token(&tok->token[i]);
				tok->token[i].litteral = ft_substr(tok->source, tok->start, (tok->cur - tok->start));
				tok->nb_token += 1;
				tok->token[i].position = tok->nb_token;
				i++;
			}
		}

    }
	i = 0;
	while(i < word)
	{
		printf("token %d pos %d = %s\n", i, tok->token[i].position, tok->token[i].litteral);
		i++;
	}
	return(0);
}
