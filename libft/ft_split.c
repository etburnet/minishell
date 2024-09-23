/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:30:20 by eburnet           #+#    #+#             */
/*   Updated: 2024/06/10 13:32:20 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_words(char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*ft_copy_word(char *s, char c)
{
	char	*word;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_free_all(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	ft_process_word(char const *s, char c, char **result, int *j)
{
	int	i;
	int	in_word;

	i = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (!in_word)
			{
				result[*j] = ft_copy_word((char *)(s + i), c);
				if (!result[*j])
					return (ft_free_all(result), -1);
				(*j)++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		j;
	char	**result;

	j = 0;
	if (!s)
		return (NULL);
	word_count = ft_count_words((char *)s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (ft_process_word(s, c, result, &j) == -1)
		return (NULL);
	result[word_count] = NULL;
	return (result);
}

/* #include <stdio.h>
int	main()
{
	char **result = ft_split("YO cv les gars", '_');
	int i = 0;
	while (result[i] != NULL) {
		printf("Partie %d : %s\n", i, result[i]);
		i++;
	}
} */