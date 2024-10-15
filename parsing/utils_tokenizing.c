/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:54 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/14 17:36:57 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     check_quote(const char *s, int i, char c)
{
    int quote;
    
    quote = 0;
    if(s[i] == c)
    {
        i++;
        quote = 1;
        while(s[i] != c && s[i] != '\0')
            i++;
        if(s[i] == c)
        { 
            quote = 0;
            i++;
        }
        if(s[i] == '\0' && quote == 1)
            return(-1);
    }
    return(i);
}

size_t    ft_countword(const char *s, int i)
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
            if(i == -1)
                return(-1);
            i = check_quote(s, i, '\'');
            if(i == -1)
                return(-1);
            while (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\0')
                i++;
            if(s[i] == ' ' || s[i] == '\0')
                count++;
        }
    }
    return (count);
}

int	ft_strchr_edit(const char *s, char c)
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
