/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:25:51 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/10 12:48:52 by eburnet          ###   ########.fr       */
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

	str = (char *)s;
	slen = ft_strlen(s);
	cpy = (char *)malloc(slen + 1);
	i = 0;
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