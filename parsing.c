/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:54 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/25 18:53:41 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t    ft_countword(const char *s, char c)
{
    size_t    i;
    size_t    count;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        if (s[i] != c && s[i] != '\'' && s[i] != '\"')
        {
            count++;
            while (s[i] != '\"' && s[i] != '\'' && s[i] != c && s[i] != '\0')
                i++;
            
        }
        else
        {
            i++;
            if(s[i] == '\'' && s[i] != '\0')
            {
                count++;
                i++;
                while(s[i] != '\'' && s[i] != '\0')
                    i++;
            }
            if(s[i] == '\"' && s[i] != '\0')
            {
                count++;
                i++;
                while(s[i] != '\"' && s[i] != '\0')
                    i++;
            }
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
	// token->litteral = NULL;
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
        if (s[tok->cur] != ' ' && s[tok->cur]!= '\'' && s[tok->cur] != '\"')
        {
			tok->start = tok->cur;
            while (s[tok->cur] != ' ' && s[tok->cur] != '\0')
			{
				tok->cur++;
				if(s[tok->cur] == ' ' || s[tok->cur] == '\0')
				{
					init_token(&tok->token[i]);
					tok->token[i].litteral = ft_substr(s, tok->start, (tok->cur - tok->start));
					tok->nb_token += 1;
					tok->token[i].position = tok->nb_token;
					i++;
				}
            	// if(s[tok->cur] == '\'' && s[tok->cur] != '\0')
				// {
				// 	tok->cur++;
				// 	quote = 1;
				// 	while(s[tok->cur] != '\"' && s[tok->cur] != '\0')
                // 	{
                //     	tok->cur++;
				// 		if(s[tok->cur] == '\"')
				// 		{
                //     		tok->cur++;
				// 			quote = 0;
				// 		}
				// 	}
				// }
				// if(quote == 1)
				// 	ft_error();
			} 
        }
        else
        {
            tok->cur++;
            if(s[tok->cur] == '\'' && s[tok->cur] != '\0')
            {
				tok->start = tok->cur;
                tok->cur++;
                while(s[tok->cur] != '\'' && s[tok->cur] != '\0')
				{
                    tok->cur++;
					if(s[tok->cur] == '\'')
					{
						while(s[tok->cur] != ' ')
							tok->cur++;
						init_token(&tok->token[i]);
						tok->token[i].litteral = ft_substr(s, tok->start, (tok->cur - tok->start) + 1);
						tok->nb_token += 1;
						tok->token[i].position = tok->nb_token;
						i++;
						break;
					}
				}
            }
            if(s[tok->cur] == '\"' && s[tok->cur] != '\0')
            {
                tok->start = tok->cur;
                tok->cur++;
                while(s[tok->cur] != '\"' && s[tok->cur] != '\0')
                {
                    tok->cur++;
					if(s[tok->cur] == '\"')
					{
						while(s[tok->cur] != ' ')
							tok->cur++;
						init_token(&tok->token[i]);
						tok->token[i].litteral = ft_substr(s, tok->start, (tok->cur - tok->start) + 1);
						tok->nb_token += 1;
						tok->token[i].position = tok->nb_token;
						i++;
						break;
					}
				}
            }
        }
    }
	i = 0;
	while(i < word)
	{
		printf("token num %d = %s\n", i, tok->token[i].litteral);
		i++;
	}
	return(0);
}
