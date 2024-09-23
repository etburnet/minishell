/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:33:50 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/09 16:26:56 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_is_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	total;
	size_t	i;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	i = 0;
	end = ft_strlen((char *)s1);
	while (s1[start] && ft_is_set(s1[start], set))
		start++;
	while (end > start && ft_is_set(s1[end - 1], set))
		end--;
	total = end - start;
	trimmed = malloc(sizeof(char) * (total + 1));
	if (trimmed == NULL)
		return (NULL);
	while (i <= total)
		trimmed[i++] = s1[start++];
	trimmed[total] = '\0';
	return (trimmed);
}

/* #include <stdio.h>
int main(void)
{
	char str[] = "AQSalut   AQ les gars cv   ?AQAQ";
	printf("%s", ft_strtrim(str, "AQ"));
} */