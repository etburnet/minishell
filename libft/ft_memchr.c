/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:03:46 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/09 12:37:46 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>
int	main()
{
	int i = 3;
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	char *rslt = ft_memchr(s, 2 + 256, i);
	while (i >= 0)
	{
		printf("Indice %d du tableau: %d\n", i, rslt[i]);
		i--;
	}
} */