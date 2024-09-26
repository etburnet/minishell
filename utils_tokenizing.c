/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:54 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/26 18:13:12 by opdi-bia         ###   ########.fr       */
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
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*news;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if (s == 0)
		return (NULL);
	while (s[size] != '\0')
		size++;
	if (start >= size)
		len = 0;
	if ((len > start + size || start + len > size) && start < size)
		len = size - start;
	news = malloc((len + 1) * sizeof(char));
	if (news == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && start < size)
	{
		news[i] = s[start + i];
		i++;
	}
	news[i] = '\0';
	return (news);
}
