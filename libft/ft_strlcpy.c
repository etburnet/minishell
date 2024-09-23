/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:27:22 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/09 14:07:10 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*s;

	s = (char *)src;
	i = 0;
	if (size > 0)
	{
		while (s[i] && i < (size - 1))
		{
			dst[i] = s[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (s[i] != '\0')
		i++;
	return (i);
}

/* #include <stdio.h>
int main()
{
	char dest[10]; memset(dest, 'A', 10);
	char src[] = "coucou";
	printf("%s\n", dest);
	printf("%s\n", src);
	printf("%ld\n", ft_strlcpy(dest, src, -1));
	printf("%d\n", !strcmp(src, dest));
	printf("%s\n", dest);
	printf("%s\n", src);
} */