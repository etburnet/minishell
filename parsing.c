/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:54 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/25 14:44:49 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static size_t    ft_countword(const char *s, char c)
// {
//     size_t    i;
//     size_t    count;

//     i = 0;
//     count = 0;
//     while (s[i] != '\0')
//     {
//         if (s[i] != c && s[i] != '\'' && s[i] != '\"')
//         {
//             count++;
//             while (s[i] != '\"' && s[i] != '\'' && s[i] != c && s[i] != '\0')
//                 i++;
            
//         }
//         else
//         {
//             i++;
//             if(s[i] == '\'' && s[i] != '\0')
//             {
//                 count++;
//                 i++;
//                 while(s[i] != '\'' && s[i] != '\0')
//                     i++;
//             }
//             if(s[i] == '\"' && s[i] != '\0')
//             {
//                 count++;
//                 i++;
//                 while(s[i] != '\"' && s[i] != '\0')
//                     i++;
//             }
//         }
//     }
//     return (count);
// }

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

void	init_tokenizer_state(t_tokenizer *tok, char *s)
{
	tok->nb_token = 0;
	tok->lenght = 0;
	tok->source = s;
	tok->cur = 0;
	tok->source_lenght = ft_strlen(s);
	tok->start = 0;
}

int		check_arg(char *s)
{
	t_tokenizer tok;
	int i;
	
	i = 0;
	init_tokenizer_state(&tok, s);
	while (s[tok.cur] != '\0')
    {
        if (s[tok.cur] != ' ' && s[tok.cur]!= '\'' && s[tok.cur] != '\"')
        {
			tok.start = tok.cur;
            while (s[tok.cur] != '\"' && s[tok.cur] != '\'' && s[tok.cur] != ' ' && s[tok.cur] != '\0')
			{
				tok.cur++;
				if(s[tok.cur] == ' ' || s[tok.cur] != '\0')
				{
					tok.token[i].litteral = ft_substr(s, tok.start, tok.start - tok.cur);
					tok.nb_token += 1;
					tok.token[i].position = (int)tok.nb_token;
					i++;
				}
			} 
        }
        else
        {
            tok.cur++;
            if(s[tok.cur] == '\'' && s[tok.cur] != '\0')
            {
				tok.start = tok.cur;
                tok.cur++;
                while(s[tok.cur] != '\'' && s[tok.cur] != '\0')
				{
                    tok.cur++;
					if(s[tok.cur] == '\'')
					{
						tok.token[i].litteral = ft_substr(s, tok.start, tok.start - tok.cur);
						tok.nb_token += 1;
						tok.token[i].position = (int)tok.nb_token;
						i++;
					}
				}
            }
            if(s[tok.cur] == '\"' && s[tok.cur] != '\0')
            {
                tok.start = tok.cur;
                tok.cur++;
                while(s[tok.cur] != '\"' && s[tok.cur] != '\0')
                {
                    tok.cur++;
					if(s[tok.cur] == '\"')
					{
						tok.token[i].litteral = ft_substr(s, tok.start, tok.start - tok.cur);
						tok.nb_token += 1;
						tok.token[i].position = (int)tok.nb_token;
						i++;
					}
				}
            }
        }
    }
	i = 0;
	while(tok.token[i].litteral)
	{
		printf("%s\n", tok.token[i].litteral);
		i++;
	}
	return(0);
}
