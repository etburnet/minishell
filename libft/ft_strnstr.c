/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:35:07 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/10 15:05:38 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *str_a, const char *str_b, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((str_a == NULL || str_b == NULL) && n == 0)
		return (0);
	while (str_a[i] != '\0' && i < n)
	{
		j = 0;
		while (str_a[i + j] == str_b[j] && str_b[j] != '\0' && (i + j) < n)
			j++;
		if (str_b[j] == '\0')
			return ((char *)(str_a + i));
		i++;
	}
	if (str_b[0] == '\0')
		return ((char *)str_a);
	return (NULL);
}

/* #include <stdio.h>
int	main(void)
{
	char	haystack[30] = "Salut les gars";
	char	needle[10] = "les";
	size_t	size = 9;

	printf("%s", ft_strnstr(haystack, needle, size));
} */