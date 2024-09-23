/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:17:34 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/08 06:50:19 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		i;
	char	*result;

	if (!s1)
		return (NULL);
	i = 0;
	lens1 = ft_strlen(s1);
	result = malloc(sizeof(char) * (lens1 + ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
	while (*s1 != '\0')
		result[i++] = *(s1++);
	i = 0;
	while (*s2 != '\0')
		result[lens1 + i++] = *(s2++);
	result[lens1 + i] = '\0';
	return (result);
}

/* #include  <stdio.h>
int main()
{
	char s1[] = "hey";
	char s2[] = ", cv ?";
	printf("%s", ft_strjoin(s1, s2));
} */