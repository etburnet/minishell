/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:53:05 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/24 18:33:35 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static size_t	ft_sizeword(char const *s, char c, int start)
{
	size_t	i;

	i = start;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i - start);
}

static char	**ft_mallocstr(char **tab, int index, size_t size)
{
	tab[index] = malloc((size + 1) * sizeof(char));
	if (tab[index] == NULL)
		return (NULL);
	return (tab);
}

static void	ft_str(char **tab, const char *s, char c, size_t len)
{
	size_t	size;
	int		i;
	int		index;
	int		start;

	index = 0;
	start = 0;
	while (index < (int)len)
	{
		while (s[start] == c)
			start++;
		size = ft_sizeword(s, c, start);
		ft_mallocstr(tab, index, size);
		i = 0;
		while (i < (int)size)
		{
			tab[index][i] = s[start + i];
			i++;
		}
		tab[index][i] = '\0';
		start = start + i;
		index++;
	}
	tab[index] = NULL;
}

char	**ft_split(char const *s,char **tab, char c, size_t len)
{

	if (!s)
		return (NULL);
	ft_str(tab, s, c, len);
	return (tab);
}

