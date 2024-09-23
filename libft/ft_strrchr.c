/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:07:26 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/09 16:46:53 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		slen;

	slen = ft_strlen((char *)s);
	while (slen >= 0)
	{
		if (s[slen] == (char)c)
			return ((char *)&s[slen]);
		slen--;
	}
	return (NULL);
}

/* #include <stdio.h>
int	main(void)
{
	char	str2[] = "bonjour";
	int		c;
	
	c = 108; //"l" ASCII
	printf("%s", ft_strrchr(str2, 's'));
} */