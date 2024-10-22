/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:25:51 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/18 12:05:10 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		slen;
	char	*str;
	char	*cpy;

	i = 0;
	str = (char *)s;
	slen = ft_strlen(str);
	cpy = (char *)malloc(slen + 1);
	if (cpy == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/* #include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strdup("Salut guys"));
} */